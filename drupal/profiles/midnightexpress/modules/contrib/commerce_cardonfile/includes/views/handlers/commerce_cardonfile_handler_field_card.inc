<?php

/**
 * @file
 * Contains the basic card field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to an card.
 */
class commerce_cardonfile_handler_field_card extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_card']) &&
      in_array($this->options['link_to_card'], array('customer', 'admin'))) {
      $this->additional_fields['card_id'] = 'card_id';
      $this->additional_fields['uid'] = 'uid';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_card'] = array('default' => 'none');

    return $options;
  }

  /**
   * Provide the link to card option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_card'] = array(
      '#type' => 'radios',
      '#title' => t('Link this field to'),
      '#description' => t('If Customer or Administrator are selected, this will override any other link you have set.'),
      '#options' => array(
        'none' => t('Nothing, unless specified in <em>Rewrite results</em> below'),
        'customer' => t('The customer view page'),
        'admin' => t('The administrator view page'),
      ),
      '#default_value' => $this->options['link_to_card'],
    );
  }

  /**
   * Render whatever the data is as a link to the card.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_card']) && in_array($this->options['link_to_card'], array('customer', 'admin')) && $data !== NULL && $data !== '') {
      $uid = $this->get_value($values, 'uid');
      $card_id = $this->get_value($values, 'card_id');

      if ($this->options['link_to_card'] == 'customer' && $uid) {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = 'user/' . $uid . '/' . 'cards/' . $card_id;
      }
      elseif ($this->options['link_to_card'] == 'admin') {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = 'admin/commerce/cards/' . $card_id;
      }
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
