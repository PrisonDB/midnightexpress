<?php

/**
 * @file
 * Default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_dunning_default_rules_configuration() {
  $items = array();

  // Component: Rule: Charge card.
  $items['rules_commerce_dunning_charge_card'] = entity_import('rules_config', '{ "rules_commerce_dunning_charge_card" : {
      "LABEL" : "Charge card",
      "PLUGIN" : "rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "commerce_payment", "commerce_cardonfile" ],
      "USES VARIABLES" : { "order" : { "label" : "Order", "type" : "commerce_order" } },
      "IF" : [
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "order" ], "operator" : "\u003E", "value" : "0" } }
      ],
      "DO" : [
        { "commerce_cardonfile_order_select_card" : {
            "USING" : { "order" : [ "order" ] },
            "PROVIDE" : { "select_card_response" : { "select_card_response" : "Select card response" } }
          }
        },
        { "commerce_cardonfile_order_charge_card" : {
            "USING" : {
              "order" : [ "order" ],
              "charge" : [ "" ],
              "select_card_response" : [ "select-card-response" ],
              "card_data" : [ "" ]
            },
            "PROVIDE" : { "charge_card_response" : { "charge_card_response" : "Charge Card Response" } }
          }
        }
      ]
    }
  }');

  // Component: Action set: Terminate dunning cycle.
  $items['rules_commerce_dunning_terminate_dunning_cycle'] = entity_import('rules_config', '{ "rules_commerce_dunning_terminate_dunning_cycle" : {
      "LABEL" : "Terminate dunning cycle",
      "PLUGIN" : "action set",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "commerce_dunning", "rules" ],
      "USES VARIABLES" : { "order" : { "label" : "Order", "type" : "commerce_order" } },
      "ACTION SET" : [
        { "commerce_dunning_invoke_dunning_end" : { "order" : [ "order" ] } },
        { "data_set" : { "data" : [ "order:status" ], "value" : "dunning_past_due" } },
        { "commerce_dunning_unschedule_tasks" : { "order" : [ "order" ] } }
      ]
    }
  }');

  // Component: Rule set: Update the order status to the appropriate declined
  // status.
  $items['rules_commerce_dunning_update_order_status_charge_decline'] = entity_import('rules_config', '{ "rules_commerce_dunning_update_order_status_charge_decline" : {
      "LABEL" : "Update the order status to the appropriate declined status",
      "PLUGIN" : "rule set",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "commerce_order" ],
      "USES VARIABLES" : {
        "response" : {
          "label" : "Charge card response",
          "type" : "commerce_cardonfile_charge_card_response"
        },
        "order" : { "label" : "Order", "type" : "commerce_order" }
      },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "data_is" : {
                  "data" : [ "response:code" ],
                  "op" : "IN",
                  "value" : { "value" : {
                      "method_failure" : "method_failure",
                      "method_failure_insufficient_funds" : "method_failure_insufficient_funds",
                      "method_failure_limit_exceeded" : "method_failure_limit_exceeded",
                      "method_failure_call_issuer" : "method_failure_call_issuer",
                      "method_failure_temporary_hold" : "method_failure_temporary_hold",
                      "method_failure_generic_decline" : "method_failure_generic_decline",
                      "method_failure_gateway_error" : "method_failure_gateway_error",
                      "method_failure_gateway_unavailable" : "method_failure_gateway_unavailable",
                      "method_failure_gateway_configuration_error" : "method_failure_gateway_configuration_error"
                    }
                  }
                }
              }
            ],
            "DO" : [
              { "commerce_order_update_status" : {
                  "commerce_order" : [ "order" ],
                  "order_status" : "cardonfile_payment_failed_soft_decline"
                }
              }
            ],
            "LABEL" : "Change order status to Payment failed (soft decline)"
          }
        },
        { "RULE" : {
            "IF" : [
              { "data_is" : {
                  "data" : [ "response:code" ],
                  "op" : "IN",
                  "value" : { "value" : {
                      "insufficient" : "insufficient",
                      "card_na" : "card_na",
                      "card_not_chargeable" : "card_not_chargeable",
                      "no_method" : "no_method",
                      "method_not_capable" : "method_not_capable",
                      "card_expired" : "card_expired",
                      "method_failure_hard_decline" : "method_failure_hard_decline"
                    }
                  }
                }
              }
            ],
            "DO" : [
              { "commerce_order_update_status" : {
                  "commerce_order" : [ "order" ],
                  "order_status" : "cardonfile_payment_error_hard_decline"
                }
              }
            ],
            "LABEL" : "Change order status to Payment error (hard decline)"
          }
        }
      ]
    }
  }');

  return $items;
}
