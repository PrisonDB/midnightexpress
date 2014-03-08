<?php

/**
 * @file
 * Default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_dunning_defaults_default_rules_configuration() {
  $items = array();

  // Component: Rule: Send dunning notification.
  $items['rules_commerce_dunning_send_notification'] = entity_import('rules_config', '{ "rules_commerce_dunning_send_notification" : {
      "LABEL" : "Send dunning notification",
      "PLUGIN" : "rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "message_notify" ],
      "USES VARIABLES" : {
        "message" : { "label" : "Message", "type" : "message" },
        "order" : { "label" : "Order", "type" : "commerce_order" },
        "card" : { "label" : "Card", "type" : "commerce_cardonfile" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "message" ], "field" : "commerce_dunning_message_order" } },
        { "entity_has_field" : { "entity" : [ "message" ], "field" : "commerce_dunning_message_card" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "message:commerce_dunning_message_order" ],
            "value" : [ "order" ]
          }
        },
        { "data_set" : {
            "data" : [ "message:commerce-dunning-message-card" ],
            "value" : [ "card" ]
          }
        },
        { "entity_save" : { "data" : [ "message" ], "immediate" : 1 } },
        { "message_notify_process" : { "message" : [ "message" ] } }
      ]
    }
  }');

  // Component: Rule: Send dunning notification — no card available.
  $items['rules_commerce_dunning_send_notification_no_card'] = entity_import('rules_config', '{ "rules_commerce_dunning_send_notification_no_card" : {
      "LABEL" : "Send dunning notification \u2014 no card available",
      "PLUGIN" : "rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "message_notify" ],
      "USES VARIABLES" : {
        "message" : { "label" : "Message", "type" : "message" },
        "order" : { "label" : "Order", "type" : "commerce_order" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "message" ], "field" : "commerce_dunning_message_order" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "message:commerce_dunning_message_order" ],
            "value" : [ "order" ]
          }
        },
        { "entity_save" : { "data" : [ "message" ], "immediate" : 1 } },
        { "message_notify_process" : { "message" : [ "message" ] } }
      ]
    }
  }');

  // Reaction rule: Notify customer about a hard declined transaction.
  $items['rules_commerce_dunning_send_notification_hard_declined'] = entity_import('rules_config', '{ "rules_commerce_dunning_send_notification_hard_declined" : {
      "LABEL" : "Notify customer about a hard declined transaction",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_failed" ],
      "IF" : [
        { "data_is" : {
            "data" : [ "response:code" ],
            "op" : "IN",
            "value" : { "value" : {
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
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "commerce_dunning_hard_declined_card",
              "param_user" : [ "order:owner" ]
            },
            "PROVIDE" : { "entity_created" : { "message_entity_created" : "Created message entity" } }
          }
        },
        { "component_rules_commerce_dunning_send_notification" : {
            "message" : [ "message-entity-created" ],
            "order" : [ "order" ],
            "card" : [ "response:card-chosen" ]
          }
        },
        { "data_set" : { "data" : [ "response:card-chosen:status" ], "value" : "3" } }
      ]
    }
  }');

  // Reaction rule: Notify customer about a soft declined transaction.
  $items['rules_commerce_dunning_send_notification_soft_declined'] = entity_import('rules_config', '{ "rules_commerce_dunning_send_notification_soft_declined" : {
      "LABEL" : "Notify customer about a soft declined transaction",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_failed" ],
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
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "commerce_dunning_soft_declined_card",
              "param_user" : [ "order:owner" ]
            },
            "PROVIDE" : { "entity_created" : { "message_entity_created" : "Created message entity" } }
          }
        },
        { "component_rules_commerce_dunning_send_notification" : {
            "message" : [ "message-entity-created" ],
            "order" : [ "order" ],
            "card" : [ "response:card-chosen" ]
          }
        }
      ]
    }
  }');

  // Reaction rule: Notify customer about a non-available card.
  $items['rules_commerce_dunning_send_notification_no_card_available'] = entity_import('rules_config', '{ "rules_commerce_dunning_send_notification_no_card_available" : {
      "LABEL" : "Notify customer about a non-available card",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_failed" ],
      "IF" : [
        { "data_is" : {
            "data" : [ "response:code" ],
            "op" : "IN",
            "value" : { "value" : { "insufficient" : "insufficient", "card_na" : "card_na" } }
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "commerce_dunning_no_card",
              "param_user" : [ "order:owner" ]
            },
            "PROVIDE" : { "entity_created" : { "message_entity_created" : "Created message entity" } }
          }
        },
        { "component_rules_commerce_dunning_send_notification_no_card" : { "message" : [ "message-entity-created" ], "order" : [ "order" ] } }
      ]
    }
  }');

  // Reaction rule: Schedule charge attempts.
  $items['rules_commerce_dunning_schedule_charge_attempts'] = entity_import('rules_config', '{ "rules_commerce_dunning_schedule_charge_attempts" : {
      "LABEL" : "Schedule charge attempts",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-10",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "commerce_dunning", "rules", "rules_scheduler", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_failed" ],
      "IF" : [
        { "NOT commerce_dunning_order_revision_status" : {
            "order" : [ "order" ],
            "status" : { "value" : {
                "cardonfile_payment_error_hard_decline" : "cardonfile_payment_error_hard_decline",
                "cardonfile_payment_failed_soft_decline" : "cardonfile_payment_failed_soft_decline"
              }
            }
          }
        }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_commerce_dunning_charge_card",
            "date" : "+3 days",
            "identifier" : "dunning-[order:order-id]-charge-attempt-3-days",
            "param_order" : [ "order" ]
          }
        },
        { "schedule" : {
            "component" : "rules_commerce_dunning_charge_card",
            "date" : "+10 days",
            "identifier" : "dunning-[order:order-id]-charge-attempt-10-days",
            "param_order" : [ "order" ]
          }
        },
        { "schedule" : {
            "component" : "rules_commerce_dunning_charge_card",
            "date" : "+14 days",
            "identifier" : "dunning-[order:order-id]-charge-attempt-14-days",
            "param_order" : [ "order" ]
          }
        },
        { "schedule" : {
            "component" : "rules_commerce_dunning_terminate_dunning_cycle",
            "date" : "+15 days",
            "identifier" : "dunning-[order:order-id]-end-15-days",
            "param_order" : [ "order" ]
          }
        }
      ]
    }
  }');

  // Reaction rule: Unschedule all further dunning steps.
  $items['rules_commerce_dunning_unschedule_all_further_steps'] = entity_import('rules_config', '{ "rules_commerce_dunning_unschedule_all_further_steps" : {
      "LABEL" : "Unschedule all further dunning steps",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "commerce_payment", "commerce_dunning", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_success" ],
      "IF" : [
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "order" ], "value" : "0" } }
      ],
      "DO" : [ { "commerce_dunning_unschedule_tasks" : { "order" : [ "order" ] } } ]
    }
  }');

  // Reaction rule: Update the order status to a charge failure status.
  $items['rules_commerce_dunning_update_order_status_charge_failure'] = entity_import('rules_config', '{ "rules_commerce_dunning_update_order_status_charge_failure" : {
      "LABEL" : "Update the order status to a charge failure status",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "10",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "rules", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_failed" ],
      "DO" : [
        { "component_rules_commerce_dunning_update_order_status_charge_decline" : { "response" : [ "response" ], "order" : [ "order" ] } }
      ]
    }
  }');

  // Reaction rule: Update the order status to charge succeeded status.
  $items['rules_commerce_dunning_update_order_status_charge_success'] = entity_import('rules_config', '{ "rules_commerce_dunning_update_order_status_charge_success" : {
      "LABEL" : "Update the order status to charge succeeded status",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "10",
      "TAGS" : [ "Commerce Dunning" ],
      "REQUIRES" : [ "commerce_order", "commerce_cardonfile" ],
      "ON" : [ "commerce_cardonfile_charge_success" ],
      "DO" : [
        { "commerce_order_update_status" : { "commerce_order" : [ "order" ], "order_status" : "cardonfile_charged" } }
      ]
    }
  }');

  return $items;
}
