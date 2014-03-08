<?php

/**
 * @file
 * Views integration for Commerce Card on File.
 */

/**
 * Implements hook_views_data().
 */
function commerce_cardonfile_views_data() {
  $data = array();

  $data['commerce_cardonfile']['table']['group']  = t('Commerce Card on File');

  $data['commerce_cardonfile']['table']['base'] = array(
    'field' => 'card_id',
    'title' => t('Commerce Card on File'),
    'help' => t('A Local Tokenized Representation of a Remotely Stored Credit Card.'),
    'access query tag' => 'commerce_cardonfile_access',
  );
  $data['commerce_cardonfile']['table']['entity type'] = 'commerce_cardonfile';

  // Card id.
  $data['commerce_cardonfile']['card_id'] = array(
    'title' => t('Card ID', array(), array('context' => 'a drupal commerce card on file')),
    'help' => t('The unique internal identifier of the card.'),
    'field' => array(
      'handler' => 'commerce_cardonfile_handler_field_card',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Card owner uid.
  $data['commerce_cardonfile']['uid'] = array(
    'title' => t('Uid'),
    'help' => t("The owner's user ID."),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name',
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'title' => t('Owner'),
      'help' => t("Relate this card to its owner's user account"),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('Card owner'),
    ),
  );

  // Card payment method.
  $data['commerce_cardonfile']['payment_method'] = array(
    'title' => t('Payment method'),
    'help' => t('The payment method related to this card.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card instance id.
  $data['commerce_cardonfile']['instance_id'] = array(
    'title' => t('Payment method instance ID'),
    'help' => t('The payment method instance ID related to this card.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card remote id.
  $data['commerce_cardonfile']['remote_id'] = array(
    'title' => t('Card data remote ID'),
    'help' => t('The remote ID to the full card data at the payment gateway.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card card_type.
  $data['commerce_cardonfile']['card_type'] = array(
    'title' => t('Card type'),
    'help' => t('The credit card type.'),
    'field' => array(
      'handler' => 'commerce_cardonfile_handler_field_card_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card card_name.
  $data['commerce_cardonfile']['card_name'] = array(
    'title' => t('Name on the card'),
    'help' => t('The name on the credit card.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card card_number.
  $data['commerce_cardonfile']['card_number'] = array(
    'title' => t('Card number'),
    'help' => t('Truncated number of the credit card (last 4 digits).'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Card expiration month.
  $data['commerce_cardonfile']['card_exp_month'] = array(
    'title' => t('Card expiration month'),
    'help' => t('Expiration month of the credit card.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Card expiration year.
  $data['commerce_cardonfile']['card_exp_year'] = array(
    'title' => t('Card expiration year'),
    'help' => t('Expiration year of the credit card.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Card status.
  $data['commerce_cardonfile']['status'] = array(
    'title' => t('Card data status'),
    'help' => t('Status of the card data storage.'),
    'field' => array(
      'handler' => 'commerce_cardonfile_handler_field_card_status',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_cardonfile_handler_filter_card_status',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Card created timestamp.
  $data['commerce_cardonfile']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date when this card was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Default card.
  $data['commerce_cardonfile']['instance_default'] = array(
    'title' => t('Default card'),
    'help' => t('Whether or not this is the default card for the Payment Instance ID.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'boolean' => array(1, 0),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Default'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose links to operate on the order.
  $data['commerce_cardonfile']['view_card'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the administrator view of the card.'),
      'handler' => 'commerce_cardonfile_handler_field_card_link',
    ),
  );
  $data['commerce_cardonfile']['edit_card'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the card.'),
      'handler' => 'commerce_cardonfile_handler_field_card_link_edit',
    ),
  );
  $data['commerce_cardonfile']['delete_card'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the card.'),
      'handler' => 'commerce_cardonfile_handler_field_card_link_delete',
    ),
  );
  // Operation links.
  $data['commerce_cardonfile']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all the available operations links for the cards.'),
      'handler' => 'commerce_cardonfile_handler_field_card_operations',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function commerce_cardonfile_views_plugins() {
  return array(
    'argument validator' => array(
      'commerce_cof_card_id' => array(
        'title' => t('Card ID access'),
        'handler' => 'commerce_cardonfile_plugin_argument_validate_card_id',
      ),
      'commerce_cof_owner' => array(
        'title' => t('Card owner access'),
        'handler' => 'commerce_cardonfile_plugin_argument_validate_owner',
      ),
    ),
  );
}
