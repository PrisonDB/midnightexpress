<?php

/**
 * @file
 * Argument plugin for a valid access to card data.
 */

/**
 * Validate whether an argument is a valid user.
 */
class commerce_cardonfile_plugin_argument_validate_card_id extends views_plugin_argument_validate {
  function validate_argument($argument) {
    global $user;

    if (is_numeric($argument) && $argument == intval($argument)) {
      $card_data = commerce_cardonfile_load($argument);
      if (!empty($card_data) && is_array($card_data)) {
        if (commerce_cardonfile_access('view', $card_data)) {
          $this->_set_allowed_argument($card_data);
          return TRUE;
        }
      }
    }

    return FALSE;
  }

  /**
   * Sets argument properties for an allowed argument
   */
  private function _set_allowed_argument($card_data) {
    dpm($card_data);
    $this->argument->argument = $card_data['card_id'];
    $this->argument->validated_title = check_plain($card_data['card_id']);
  }
}
