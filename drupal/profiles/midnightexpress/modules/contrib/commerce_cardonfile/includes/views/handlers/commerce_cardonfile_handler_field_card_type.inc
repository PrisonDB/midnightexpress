<?php

/**
 * Field handler to translate a card type name into its readable form.
 */
class commerce_cardonfile_handler_field_card_type extends views_handler_field {
  function render($values) {
    $value = $this->get_value($values);

    // Load the credit card helper functions from the Payment module.
    commerce_cardonfile_load_credit_card_helpers();
    $card_types = commerce_payment_credit_card_types();

    // Extract the name of the card type if possible.
    if (!empty($card_types[$value])) {
      $value = $card_types[$value];
    }

    return $this->sanitize_value($value);
  }
}
