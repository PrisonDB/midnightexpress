<?php

/**
 * Filter by order status.
 */
class commerce_cardonfile_handler_filter_card_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = commerce_cardonfile_status_options_list();
    }
  }
}
