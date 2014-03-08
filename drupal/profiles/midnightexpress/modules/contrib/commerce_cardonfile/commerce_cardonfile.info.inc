<?php

/**
 * @file
 * Provides metadata for the commerce cardonfile entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_cardonfile_entity_property_info() {
  $info = array();

  // Add meta-data about the basic commerce_product properties.
  $properties = &$info['commerce_cardonfile']['properties'];

  $properties['card_id'] = array(
    'label' => t('Card ID'),
    'description' => t('Serial numeric ID of the truncated card data in the local database.'),
    'type' => 'integer',
    'schema field' => 'card_id',
  );
  $properties['payment_method'] = array(
    'label' => t('Payment method'),
    'description' => t('The payment method method_id for this transaction.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'payment_method',
  );
  $properties['instance_id'] = array(
    'label' => t('Instance ID'),
    'description' => t('The payment method instance ID for this transaction.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'instance_id',
  );
  $properties['remote_id'] = array(
    'label' => t('Remote ID'),
    'description' => t('The remote ID to the full card data at the payment gateway.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'remote_id',
  );
  $properties['card_type'] = array(
    'label' => t('Card type'),
    'description' => t('The credit card type.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'card_type',
  );
  $properties['card_name'] = array(
    'label' => t('Card name'),
    'description' => t('The name on the credit card.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'card_name',
  );
  $properties['card_number'] = array(
    'label' => t('Card number'),
    'description' => t('Truncated number of the credit card (last 4 digits).'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'card_number',
  );
  $properties['card_exp_month'] = array(
    'label' => t('Card expiration month'),
    'description' => t('Expiration month of the credit card.'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'card_exp_month',
  );
  $properties['card_exp_year'] = array(
    'label' => t('Card expiration year'),
    'description' => t('Expiration year of the credit card.'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'card_exp_year',
  );
  $properties['status'] = array(
    'label' => t('Card Status'),
    'description' => t('Status of the card data: inactive (0); active (1); or active and not deletable (2).'),
    'type' => 'integer',
    'setter callback' => 'entity_property_verbatim_set',
    'options list' => 'commerce_cardonfile_statuses',
    'schema field' => 'status',
  );
  $properties['created'] = array(
    'label' => t('Created'),
    'description' => t('The Unix timestamp when the card data was first stored.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t('Changed'),
    'description' => t('The Unix timestamp when the card data was last updated.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'changed',
  );
  $properties['instance_default'] = array(
    'label' => t('Instance default'),
    'description' => t('Boolean indicating the default card for a payment instance ID.'),
    'type' => 'boolean',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'instance_default',
  );
  // User entity.
  $properties['user'] = array(
    'label' => t('User'),
    'description' => t("Owner's user account."),
    'type' => 'user',
    'setter callback' => 'entity_property_verbatim_set',
    'schema field' => 'uid',
  );

  return $info;
}
