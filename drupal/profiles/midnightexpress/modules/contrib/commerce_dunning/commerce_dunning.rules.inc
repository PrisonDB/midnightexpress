<?php

/**
 * @file
 * Provides Rules integration.
 */

/**
 * Implements hook_rules_event_info().
 */
function commerce_dunning_rules_event_info() {
  return array(
    'commerce_dunning_cycle_end' => array(
      'label' => t('After dunning cycle ended'),
      'group' => t('Commerce Dunning'),
      'variables' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function commerce_dunning_rules_condition_info() {
  return array(
    'commerce_dunning_cardonfile_status' => array(
      'label' => t('Card on file has status of'),
      'parameter' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
        'status' => array(
          'label' => t('Status'),
          'type' => 'integer',
          'options list' => 'commerce_cardonfile_statuses',
        ),
      ),
      'group' => t('Commerce Dunning'),
      'callbacks' => array(
        'execute' => 'commerce_dunning_rules_condition_cardonfile_status',
      ),
    ),
    'commerce_dunning_order_revision_status' => array(
      'label' => t('Order has a revision with status of'),
      'parameter' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
        'status' => array(
          'label' => t('Status'),
          'type' => 'list<text>',
          'options list' => 'commerce_order_status_options_list',
        ),
      ),
      'group' => t('Commerce Dunning'),
      'callbacks' => array(
        'execute' => 'commerce_dunning_rules_condition_order_revision_status',
      ),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_dunning_rules_action_info() {
  return array(
    'commerce_dunning_invoke_dunning_end' => array(
      'label' => t('Invoke dunning cycle ending event'),
      'parameter' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
      'group' => t('Commerce Dunning'),
      'callbacks' => array(
        'execute' => 'commerce_dunning_rules_action_invoke_dunning_end',
      ),
    ),
    'commerce_dunning_unschedule_tasks' => array(
      'label' => t('Unschedule further dunning steps'),
      'parameter' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order'),
        ),
      ),
      'group' => t('Commerce Dunning'),
      'callbacks' => array(
        'execute' => 'commerce_dunning_rules_action_unschedule_tasks',
      ),
    ),
  );
}

/**
 * Rules condition implementation callback: checks status of card on file.
 */
function commerce_dunning_rules_condition_cardonfile_status($order, $status) {
  $response = commerce_cardonfile_order_select_card($order);
  if ($response['code'] == COMMERCE_COF_PROCESS_CODE_CARD_OK) {
    return ($response['card_chosen']->status == $status);
  }
  return FALSE;
}

/**
 * Rules condition implementation callback: checks order revisions with status.
 */
function commerce_dunning_rules_condition_order_revision_status($order, $status) {
  return commerce_dunning_order_has_revision_with_status($order, $status);
}

/**
 * Rules action implementation callback: invokes dunning cycle ending event.
 */
function commerce_dunning_rules_action_invoke_dunning_end($order) {
  rules_invoke_all('commerce_dunning_cycle_end', $order);
}

/**
 * Rules action implementation callback: unschedules further dunning steps.
 */
function commerce_dunning_rules_action_unschedule_tasks($order) {
  foreach (commerce_dunning_get_scheduled_tasks($order->order_id) as $tid => $task) {
    rules_scheduler_task_delete($tid);
  }
}
