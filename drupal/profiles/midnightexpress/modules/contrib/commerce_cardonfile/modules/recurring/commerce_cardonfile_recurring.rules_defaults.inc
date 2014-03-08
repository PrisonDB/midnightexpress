<?php

/**
 * @file
 * Default rule configurations for Commerce Card on File recurring.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_cardonfile_recurring_default_rules_configuration() {
  $rules = array();

  $rule = rules_reaction_rule();

  $rule->label = 'Charge pending recurring orders';
  $rule->requires = array(
    'rules',
    'commerce_cardonfile',
    'commerce_recurring',
  );

  $rule->event('commerce_recurring_cron');

  $rule->action('entity_query', array(
    'type' => 'commerce_order',
    'property' => 'status',
    'value' => 'recurring_pending',
    'limit' => 5,
  ));

  $loop = rules_loop(array(
    'list:select' => 'entity-fetched',
    'item:var' => 'order',
    'item:label' => t('Current Order'),
  ));
  $loop->action('commerce_cardonfile_order_select_card', array(
    'order:select' => 'order',
  ));
  $loop->action('commerce_cardonfile_order_charge_card', array(
    'order:select' => 'order',
    'charge:select' => 'order:commerce-order-total',
    'select_card_response:select' => 'select-card-response',
    'card_data:select' => '',
  ));

  $rule->action($loop);

  $rules['charge_pending_recurring_orders'] = $rule;

  $rule = rules_reaction_rule();

  $rule->label = 'Successful recurring order card charge';
  $rule->requires = array(
    'rules',
    'commerce_cardonfile',
    'commerce_order',
  );

  $rule->event('commerce_cardonfile_charge_success');

  $rule->condition('data_is', array(
    'data:select' => 'order:status',
    'value' => 'recurring_pending',
  ));

  $rule->action('commerce_order_update_status', array(
    'commerce_order:select' => 'order',
    'order_status' => 'cardonfile_charged',
  ));

  $rules['recurring_order_card_charged'] = $rule;

  $rule = rules_reaction_rule();

  $rule->label = 'Unsuccessful recurring order card charge — soft decline';
  $rule->requires = array(
    'rules',
    'commerce_cardonfile',
    'commerce_order',
  );

  $rule->event('commerce_cardonfile_charge_failed');

  $rule->condition('data_is', array(
    'data:select' => 'response:code',
    'op' => 'IN',
    'value' => array(
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_INSUFFICIENT_FUNDS,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_LIMIT_EXCEEDED,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_CALL_ISSUER,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_TEMPORARY_HOLD,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_GENERIC_DECLINE,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_GATEWAY_ERROR,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_GATEWAY_UNAVAILABLE,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_GATEWAY_CONFIGURATION_ERROR,
    ),
  ));

  $rule->action('commerce_order_update_status', array(
    'commerce_order:select' => 'order',
    'order_status' => 'cardonfile_payment_failed_soft_decline',
  ));

  $rules['recurring_order_card_failed_soft_decline'] = $rule;

  $rule = rules_reaction_rule();

  $rule->label = 'Unsuccessful recurring order card charge — hard decline';
  $rule->requires = array(
    'rules',
    'commerce_cardonfile',
    'commerce_order',
  );

  $rule->event('commerce_cardonfile_charge_failed');

  $rule->condition('data_is', array(
    'data:select' => 'response:code',
    'op' => 'IN',
    'value' => array(
      COMMERCE_COF_PROCESS_CODE_INSUFFICIENT_DATA,
      COMMERCE_COF_PROCESS_CODE_CARD_NA,
      COMMERCE_COF_PROCESS_CODE_CARD_NOT_CHARGEABLE,
      COMMERCE_COF_PROCESS_CODE_METHOD_EMPTY,
      COMMERCE_COF_PROCESS_CODE_METHOD_NOT_CAPABLE,
      COMMERCE_COF_PROCESS_CODE_CARD_EXPIRED,
      COMMERCE_COF_PROCESS_CODE_METHOD_FAILURE_HARD_DECLINE,
    ),
  ));

  $rule->action('commerce_order_update_status', array(
    'commerce_order:select' => 'order',
    'order_status' => 'cardonfile_payment_error_hard_decline',
  ));

  $rules['recurring_order_card_failed_hard_decline'] = $rule;

  return $rules;

}
