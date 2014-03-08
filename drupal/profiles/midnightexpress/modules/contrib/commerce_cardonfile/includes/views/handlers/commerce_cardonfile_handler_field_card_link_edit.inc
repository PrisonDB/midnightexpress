<?php

/**
 * Field handler to present a card edit link.
 */
class commerce_cardonfile_handler_field_card_link_edit extends commerce_cardonfile_handler_field_card_link {
  function construct() {
    parent::construct();

    $this->additional_fields['card_id'] = 'card_id';
    $this->additional_fields['uid'] = 'uid';
  }

  function render($values) {
    // Ensure the user has access to edit this card.
    $card = commerce_cardonfile_load($this->get_value($values, 'card_id'));

    if (!commerce_cardonfile_access('update', $card)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return l($text, 'user/' . $card->uid . '/' . 'cards/' . $card->card_id . '/edit', array('query' => drupal_get_destination()));
  }
}
