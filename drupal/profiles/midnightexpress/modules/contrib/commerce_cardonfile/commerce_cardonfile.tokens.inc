<?php

/**
 * @file
 * Builds placeholder replacement tokens for Card on file related data.
 */


/**
 * Implements hook_token_info().
 */
function commerce_cardonfile_token_info() {
  $tokens = array(
    'commerce-cardonfile' => array(),
    'commerce-cardonfile-charge-card-response' => array(),
  );
  $type_props = array(
    'commerce-cardonfile-charge-card-response' => commerce_cardonfile_charge_card_response_property_info_callback(),
  );

  // Remove unsupported properties.
  unset($type_props['commerce-cardonfile']['rule_config']);
  unset($type_props['commerce-cardonfile']['payment_method_instance']);
  unset($type_props['commerce-cardonfile-charge-card-response']['card_chosen']);

  // Translate properties to tokens.
  foreach ($type_props as $type => $props) {
    $type_tokens = &$tokens[$type];
    foreach ($props as $prop_name => $prop_info) {
      $name = str_replace('_', '-', $prop_name);
      $type_tokens[$name] = array(
        'name' => $name,
        'description' => $name,
      );

      if (!empty($prop_info['label'])) {
        $type_tokens[$name]['name'] = $prop_info['label'];
      }
      if (empty($prop_info['description'])) {
        $type_tokens[$name]['description'] = $type_tokens[$name]['name'];
      }
      if (!empty($prop_info['type'])) {
        $type_tokens[$name]['type'] = str_replace('_', '-', $prop_info['type']);
      }
    }
    unset($type_tokens);
  }

  // Return definitions.
  return array(
    'types' => array(
      'commerce-cardonfile' => array(
        'name' => t('Card Data'),
        'description' => t('Tokens related to card on file data.'),
        'needs-data' => 'commerce-cardonfile',
      ),
      'commerce-cardonfile-charge-card-response' => array(
        'name' => t('Charge Card on File Response'),
        'description' => t('Tokens related to card on file charge response.'),
        'needs-data' => 'commerce-cardonfile-charge-card-response',
      ),
    ),
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function commerce_cardonfile_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $token_info = array(
    'commerce-cardonfile' => array(
      'property_type' => 'commerce_cardonfile',
    ),
    'commerce-cardonfile-charge-card-response' => array(
      'property_type' => 'commerce_cardonfile_charge_card_response',
      'property_callback' => 'commerce_cardonfile_charge_card_response_property_info_callback',
    ),
  );

  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if (empty($token_info[$type]) || empty($data[$type])) {
    return array();
  }

  $type_data = $data[$type];

  // Make a pseudo wrapper for card data.
  $wrapper_info = array();
  if(isset($token_info[$type]['property_callback'])) {
    $wrapper_info = $token_info[$type]['property_callback']();
  }
  $wrapper = new EntityStructureWrapper($token_info[$type]['property_type'], $type_data, $wrapper_info);

  foreach ($tokens as $name => $original) {
    $replacement_value = NULL;
    $property_name = str_replace('-', '_', $name);
    if (isset($wrapper->{$property_name})) {
      $property_value = $wrapper->{$property_name}->value();

      // Default values for the chained tokens handled below.
      switch ($name) {
        case 'owner':
          if (empty($type_data->uid)) {
            $name = variable_get('anonymous', t('Anonymous'));
          }
          else {
            $name = $property_value->name;
          }
          $replacement_value = $name;
          break;

        default:
          if (!is_object($property_value)) {
            $replacement_value = $property_value;
          }
          break;
      }
    }

    if (isset($replacement_value)) {
      $replacements[$original] = $sanitize ? check_plain($replacement_value) : $replacement_value;
    }
  }

  if (isset($type_data->uid) && $owner_tokens = token_find_with_prefix($tokens, 'owner')) {
    $owner = user_load($type_data->uid);
    $replacements += token_generate('user', $owner_tokens, array('user' => $owner), $options);
  }

  // Timestamp tokens.
  foreach (array('created', 'changed', 'card-exp-timestamp') as $date_token) {
    if ($date_tokens = token_find_with_prefix($tokens, $date_token)) {
      $date_property_name = str_replace('-', '_', $date_token);
      if (isset($wrapper->{$date_property_name})) {
        $date_timestamp = $wrapper->{$date_property_name}->value();
        $replacements += token_generate('date', $date_tokens, array('date' => $date_timestamp), $options);
      }
    }
  }

  return $replacements;
}
