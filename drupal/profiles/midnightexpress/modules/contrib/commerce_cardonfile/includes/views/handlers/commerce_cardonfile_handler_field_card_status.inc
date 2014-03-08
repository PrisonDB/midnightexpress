<?php

/**
 * Field handler to translate a card data status into its readable form.
 */
class commerce_cardonfile_handler_field_card_status extends views_handler_field {
  function render($values) {
    $statuses = commerce_cardonfile_statuses();
    $value = $this->get_value($values);
    if (!empty($statuses[$value])) {
      return $this->sanitize_value($statuses[$value]);
    }
  }
}
