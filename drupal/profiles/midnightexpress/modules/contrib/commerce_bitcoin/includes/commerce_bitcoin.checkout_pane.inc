<?php
/**
 * Implements base_settings_form()
 */
function commerce_bitcoin_pane_settings_form($checkout_pane) {
  $form['commerce_bitcoin_pane_field'] = array(
    '#type' => 'textfield',
    '#title' => t('My Module Pane Field'),
    '#default_value' => variable_get('commerce_bitcoin_pane_field', ''),
  );
  return $form;
}

/**
 * Implements base_checkout_form()
 * Display the bitcoin address at the checkout
 *
 */
function commerce_bitcoin_pane_checkout_form($form, $form_state, $checkout_pane, $order) {

  $checkout_form['commerce_bitcoin_pane_field_display'] = array(
    '#markup' => t('Payment address').'<br/><strong>'.check_plain($order->commerce_bitcoin['bitcoin_address']).'</strong>'
  );

  return $checkout_form;
}
