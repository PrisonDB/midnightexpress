<?php

/**
 * Field handler to present a link to an order.
 */
class commerce_cardonfile_handler_field_card_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['card_id'] = 'card_id';
    $this->additional_fields['uid'] = 'uid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $card = new stdClass();
    $card->card_id = $this->get_value($values, 'card_id');
    $card->uid = $this->get_value($values, 'uid');

    return l($text, 'user/' . $card->uid . '/' . 'cards/' . $card->card_id, array('query' => drupal_get_destination()));
  }
}
