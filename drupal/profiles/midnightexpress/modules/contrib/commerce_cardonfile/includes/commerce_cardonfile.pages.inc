<?php

/**
 * @file
 * User page callbacks and forms for Commerce Card on File.
 */

/**
 * Menu item title callback: returns a Card Title for its pages
 * comprised of the card type and last 4 digits.
 *
 * @param $card
 *   The card object as loaded via the URL wildcard.
 * @return
 *   A page title of the format "Card ##".
 */
function commerce_cardonfile_card_title($card_data) {
  return t('@type ending in @number', array('@type' => $card_data->card_type, '@number' => $card_data->card_number));
}

/**
 * Displays the full details of a Card on file.
 */
function commerce_cardonfile_card_view($card_data, $view_mode) {
  return entity_view('commerce_cardonfile', array($card_data->card_id => $card_data), $view_mode, NULL, TRUE);
}

/**
 * Returns the appropriate Card on File form.
 */
function commerce_cardonfile_card_form_page($op, $card_data, $account) {
  $payment_method = commerce_payment_method_instance_load($card_data->instance_id);

  if ($op == 'update') {
    drupal_set_title(t('Update your @type ending in @number', array('@type' => $card_data->card_type, '@number' => $card_data->card_number)));

    // This is not likely to happen, but if the payment method doesn't implement
    // the update callback, redirect the user back to the card listing page and
    // inform them about the error.
    if (!isset($payment_method['cardonfile']['update callback'])) {
      drupal_set_message(t('We encountered an error attempting to update your card data. Please try again and contact us if this error persists.'), 'error');
      drupal_goto('user/' . $card_data->uid . '/cards');
    }
  }
  else {
    drupal_set_title(t('Add new credit card'));
    // Card data was initialized with the anonymous user as its owner. Set the
    // owner here to the user from the menu item, so that the form will receive
    // the complete information that is needed to save the card.
    $card_data->uid = $account->uid;
  }

  if ($form_callback = commerce_cardonfile_payment_method_callback($payment_method, $op . ' form callback')) {
    return drupal_get_form($form_callback, $op, $card_data);
  }
  else {
    return drupal_get_form('commerce_cardonfile_card_form', $op, $card_data);
  }
}

/**
 * Builds the form for creating/updating cardonfile data.
 */
function commerce_cardonfile_card_form($form, &$form_state, $op, $card_data) {
  // Load the credit card helper functions from the Payment module.
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');

  // Pass along information to the validate and submit handlers.
  $form_state['card_data'] = $card_data;
  $form_state['op'] = $op;

  $fields = array(
    'owner' => '',
    'code' => '',
    'type' => array(
      'visa',
      'mastercard',
      'amex',
    ),
  );
  $defaults = array();
  if ($op == 'update') {
    unset($fields['code']);
    $defaults = array(
      'type' => $card_data->card_type,
      'owner' => $card_data->card_name,
      'exp_month' => $card_data->card_exp_month,
      'exp_year' => $card_data->card_exp_year,
    );
  }
  $form += commerce_payment_credit_card_form($fields, $defaults);
  if ($op == 'update') {
    $credit_card_types = commerce_payment_credit_card_types();
    $form['credit_card']['type']['#type'] = 'item';
    $form['credit_card']['type']['#markup'] = $credit_card_types[$card_data->card_type];
    $form['credit_card']['number']['#type'] = 'item';
    $form['credit_card']['number']['#markup'] = 'XXXX - XXXX - XXXX - ' . $card_data->card_number;
  }

  $payment_method = commerce_payment_method_load($card_data->payment_method);
  $form['credit_card']['cardonfile_instance_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use as default card for payments with %method', array('%method' => $payment_method['display_title'])),
    '#default_value' => FALSE,
  );
  // Disable the checkbox if we are adding a new card and the user doesn't have
  // any other active cards with the same instance ID. Also disable it, if we
  // are updating the current default card, so the user can't uncheck the
  // checkbox.
  $existing_cards = commerce_cardonfile_load_multiple_by_uid($card_data->uid, $card_data->instance_id, TRUE);
  $default_card = FALSE;
  if ($op == 'update' && !empty($existing_cards)) {
    foreach ($existing_cards as $card) {
      if ($card->instance_default) {
        if ($card->card_id == $card_data->card_id) {
          $default_card = TRUE;
        }
        break;
      }
    }
  }
  if (($op == 'create' && !$existing_cards) || ($op == 'update' && $default_card)) {
    $form['credit_card']['cardonfile_instance_default']['#default_value'] = TRUE;
    $form['credit_card']['cardonfile_instance_default']['#disabled'] = TRUE;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => ($op == 'create') ? t('Add card') : t('Update card data'),
    '#suffix' => l(t('Cancel'), 'user/' . $card_data->uid . '/cards'),
  );

  return $form;
}

/**
 * Form validate handler: create/update card data.
 */
function commerce_cardonfile_card_form_validate($form, &$form_state) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');

  if ($form_state['op'] == 'create') {
    commerce_payment_credit_card_validate($form_state['values']['credit_card'], array('form_parents' => array('credit_card')));
  }
  else {
    // Ensure the expiration date is not being updated to a past date.
    $exp_valid = commerce_payment_validate_credit_card_exp_date($form_state['values']['credit_card']['exp_month'], $form_state['values']['credit_card']['exp_year']);
    if ($exp_valid !== TRUE) {
      form_set_error('credit_card][exp_' . $exp_valid, t('You have specified an expired credit card.'));
    }
  }
}

/**
 * Form submit handler: create/update card data.
 */
function commerce_cardonfile_card_form_submit($form, &$form_state) {
  $op = $form_state['op'];
  $card_data = $form_state['card_data'];

  $card_data->card_name = $form_state['values']['credit_card']['owner'];
  $card_data->card_exp_month = $form_state['values']['credit_card']['exp_month'];
  $card_data->card_exp_year = $form_state['values']['credit_card']['exp_year'];
  if ($op == 'create') {
    $card_data->card_number = substr($form_state['values']['credit_card']['number'], -4);
    $card_data->card_type = $form_state['values']['credit_card']['type'];
  }

  // Invoke the payment method's card create/update callback.
  $payment_method = commerce_payment_method_instance_load($card_data->instance_id);
  $callback = $payment_method['cardonfile'][$op . ' callback'];
  $success = FALSE;
  if (function_exists($callback)) {
    $callback_return = $callback($form, $form_state, $payment_method, $card_data);
    if ($callback_return) {
      if ($op == 'create') {
        $card_data_save = $callback_return;
        $confirm_message = t('A new card has been added.');
      }
      else {
        $card_data_save = $card_data;
        $confirm_message = t('The stored card data has been updated.');
      }
      commerce_cardonfile_save($card_data_save);
      if (!empty($form_state['values']['credit_card']['cardonfile_instance_default'])) {
        commerce_cardonfile_set_default_card($card_data_save->card_id);
      }
      drupal_set_message($confirm_message);
      $success = TRUE;
    }
  }

  if (!$success) {
    if ($op == 'create') {
      drupal_set_message(t('We encountered an error attempting to save your card data. Please try again and contact us if this error persists.'), 'error');
    }
    else {
      drupal_set_message(t('We encountered an error attempting to update your card data. Please try again and contact us if this error persists.'), 'error');
    }
  }
  $form_state['redirect'] = 'user/' . $card_data->uid . '/cards';
}

/**
 * Builds the form for deleting cardonfile data.
 *
 */
function commerce_cardonfile_delete_form($form, &$form_state, $card_data) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');

  $card_types = commerce_payment_credit_card_types();

  $form['card_type'] = array(
    '#type' => 'item',
    '#title' => t('Card type'),
    '#markup' => !empty($card_types[$card_data->card_type]) ? $card_types[$card_data->card_type] : $card_data->card_type,
  );

  $form['card_number'] = array(
    '#type' => 'item',
    '#title' => t('Card number'),
    '#markup' => 'XXXX - XXXX - XXXX - ' . $card_data->card_number,
  );

  $form['card_expire'] = array(
    '#type' => 'item',
    '#title' => t('Expires'),
    '#markup' => $card_data->card_exp_month . ' / ' . $card_data->card_exp_year,
  );

  $form['card_holder'] = array(
    '#type' => 'item',
    '#title' => t('Card holder'),
    '#markup' => $card_data->card_name,
  );

  $form['card_data'] = array(
    '#type' => 'value',
    '#value' => $card_data,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete this card?'),
    'user/' . $card_data->uid . '/cards',
    theme('card_data_overview', array('card_data' => $card_data)),
    t('Delete')
  );
}

/**
 * Form submit handler: delete stored card data.
 */
function commerce_cardonfile_delete_form_submit($form, &$form_state) {
  $card_data = $form_state['values']['card_data'];

  // Invoke the payment method's card delete callback.
  $payment_method = commerce_payment_method_instance_load($card_data->instance_id);
  $callback = $payment_method['cardonfile']['delete callback'];

  if (function_exists($callback)) {
    if (!$callback($form, $form_state, $payment_method, $card_data)) {
      // Display a message if we failed to communicate properly with the payment
      // gateway in the Card on File delete callback.
      drupal_set_message(t('We encountered an error attempting to delete your card data. Please try again and contact us if this error persists.'), 'error');
      $form_state['redirect'] = 'user/' . $card_data->uid . '/cards';
      return;
    }
  }

  // Disable the card data but retain the record.
  $card_data->status = 0;
  commerce_cardonfile_save($card_data);

  drupal_set_message(t('The stored card data has been deleted.'));

  // Redirect to the payment methods tab if the user has other stored payment.
  $stored_cards = commerce_cardonfile_load_multiple_by_uid($card_data->uid);

  if (!empty($stored_cards)) {
    $form_state['redirect'] = 'user/' . $card_data->uid . '/cards';
  }
  else {
    $form_state['redirect'] = 'user/' . $card_data->uid;
  }
}
