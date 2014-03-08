<?php

/**
 * @file
 * Default Rules configuration.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_dunning_testing_default_rules_configuration() {
  $items = array();

  // Reaction rule: Payment rule for Commerce Dunning Testing payment.
  $items['commerce_payment_commerce_dunning_testing_payment'] = entity_import('rules_config', '{ "commerce_payment_commerce_dunning_testing_payment" : {
      "LABEL" : "Commerce Dunning Test Payment",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Payment" ],
      "REQUIRES" : [ "commerce_payment" ],
      "ON" : [ "commerce_payment_methods" ],
      "DO" : [
        { "commerce_payment_enable_commerce_dunning_testing_payment" : {
            "commerce_order" : [ "commerce-order" ],
            "payment_method" : "commerce_dunning_testing_payment"
          }
        }
      ]
    }
  }');
}
