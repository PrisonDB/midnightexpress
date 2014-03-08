<?php
/**
 * @file
 * All the flexiform hooks.
 */

/**
 * Implements hook_flexiform_group_info().
 */
function flexiform_flexiform_group_info() {
  return array(
    'general' => array(
      'label' => t('General'),
    ),
  );
}

/**
 * Implements hook_flexiform_builder_info().
 */
function flexiform_flexiform_builder_info() {
  $builders = array();

  $builders['FlexiformBuilderFlexiform'] = array(
    'class' => 'FlexiformBuilderFlexiform',
    'label' => t('Flexiform Form Builder'),
    'description' => t('The flexiform custom form builder. Use the configuration pages to add fields and entities to the form.'),
  );

  $fieldable_entities = array();
  foreach (entity_get_info() as $entity_type => $info) {
    if ($info['fieldable']) {
      $fieldable_entities[] = $entity_type;
    }
  }
  $builders['FlexiformBuilderEntityForm'] = array(
    'class' => 'FlexiformBuilderEntityForm',
    'label' => t('Entity Field Form'),
    'description' => t('Render the standard entity field form.'),
    'entity_types' => $fieldable_entities,
  );

  return $builders;
}

/**
 * Implements hook_flexiform_entity_getter_info().
 */
function flexiform_flexiform_entity_getter_info() {
  $getters = array();

  // Base entity getter.
  $getters['base_entity'] = array(
    'label' => 'Base Entity',
    'description' => 'The Base Entity for this Flexiform',
    'entity_types' => array_keys(entity_get_info()),
    'file' => 'includes/flexiform.flexiform.inc',
  );

  // User Getters
  $getters['user_current_user'] = array(
    'label' => 'Current User',
    'description' => 'Load the current user into the Form',
    'entity_types' => array('user'),
    'file' => 'user.flexiform.inc',
  );

  // Profile2 Getters
  if (module_exists('profile2')) {
    $getters['profile2_profile_from_user'] = array(
      'label' => 'Profile2 from User',
      'description' => 'Load a Profile 2 Basede on a User',
      'params' => array(
        'user' => array(
          'entity_type' => 'user',
        ),
      ),
      'entity_types' => array('profile2'),
      'file' => 'profile2.flexiform.inc',
    );
  }

  // Party Getters.
  if (module_exists('party')) {
    // Getters for data sets.
    foreach (party_get_data_set_info() as $data_set_name => $info) {
      $getters[$data_set_name . '_from_party'] = array(
        'label' => t('@label data set', array('@label' => $info['label'])),
        'description' => t('Load a data set from a party.'),
        'data_set_name' => $data_set_name,
        'getter callback' => 'flexiform_entity_getter_party_data_set',
        'setter callback' => 'flexiform_entity_setter_party_data_set',
        'params' => array(
          'party' => array(
            'entity_type' => 'party',
          ),
        ),
        'entity_types' => array($info['entity type']),
        'file' => 'party.flexiform.inc',
      );
    }

    // Party from user Getters
    $getters['party_from_user'] = array(
      'label' => 'Party from User',
      'description' => 'Load a Party Based on a User',
      'params' => array(
        'user' => array(
          'entity_type' => 'user',
        ),
      ),
      'entity_types' => array('party'),
      'file' => 'party.flexiform.inc',
    );
  }

  return $getters;
}

/**
 * Implements hook_flexiform_builder_info().
 */
function flexiform_flexiform_display_info() {
  $displays = array();

  $displays['flexiform_create_entity_page'] = array(
    'class' => 'FlexiformDisplayCreatePage',
    'label' => t('Add page'),
    'description' => t('A page to add a new submission of the form. Will create a new base entity.'),
  );

  $displays['flexiform_edit_entity_page'] = array(
    'class' => 'FlexiformDisplayEditPage',
    'label' => t('Edit page'),
    'description' => t('A page to an edit form. Will load an existing base entity.'),
  );

  if (module_exists('ctools')) {
    $displays['flexiform_edit_entity_pane'] = array(
      'class' => 'FlexiformDisplayEditPane',
      'label' => t('Edit Pane (Ctools Content)'),
      'description' => t('Expose the form in a Ctools Content Plugin.'),
    );
  }

  if (module_exists('user')) {
    $displays['flexiform_user_category'] = array(
      'class' => 'FlexiformDisplayUserCategory',
      'label' => t('User category'),
      'description' => t('Expose this form as a tab under user edit.'),
    );
  }

  return $displays;
}

/**
 * Implements hook_flexiform_element_info().
 */
function flexiform_flexiform_element_info() {
  $elements = array();

  // Get the element for all nested flexiforms.
  $forms = db_select('flexiform', 'f')
    ->fields('f', array('label', 'form', 'base_entity', 'base_entity_bundle'))
    ->execute()
    ->fetchAllAssoc('form');

  // Add custom form elements to every entity type.
  foreach (entity_get_info() as $entity_type => $info) {
    foreach ($info['bundles'] as $bundle => $info) {
      $elements[$entity_type][$bundle]['custom:html'] = array(
        'label' => t('Custom HTML'),
        'class' => 'FlexiformElementCustomHtml',
        'type' => 'custom_html',
        'group' => 'Custom',
      );
    }
  }

  foreach ($forms as $form) {
    $elements[$form->base_entity][$form->base_entity_bundle]['flexiform:' . $form->form] = array(
      'label' => $form->label,
      'class' => 'FlexiformElementFlexiform',
      'type' => 'form',
      'group' => 'Flexiform',
      'form' => $form->form,
    );
  }

  // Get all the field elements.
  $fields_info = field_info_instances();
  foreach ($fields_info as $entity_type => $entity_fields) {
    foreach ($entity_fields as $bundle => $bundle_fields) {
      foreach ($bundle_fields as $field_name => $instance) {
        $elements[$entity_type][$bundle]['field:' . $field_name] = array(
          'label' => $instance['label'],
          'class' => 'FlexiformElementField',
          'type' => 'field',
          'group' => 'Field',
          'field_name' => $field_name,
        );
      }
    }
  }

  // Get node elements
  foreach (node_type_get_types() as $bundle => $info) {
    if ($info->has_title) {
      $elements['node'][$bundle]['node:title'] = array(
        'label' => $info->title_label,
        'class' => 'FlexiformElementNodeTitle',
        'type' => 'title',
        'group' => 'Node',
      );
    }

    $elements['node'][$bundle]['node:status'] = array(
      'label' => t('Published'),
      'class' => 'FlexiformElementNodeStatus',
      'type' => 'status',
      'group' => 'Node',
    );

    $elements['node'][$bundle]['node:promote'] = array(
      'label' => t('Promoted to front page'),
      'class' => 'FlexiformElementNodePromote',
      'type' => 'promote',
      'group' => 'Node',
    );

    $elements['node'][$bundle]['node:sticky'] = array(
      'label' => t('Sticky at top of lists'),
      'class' => 'FlexiformElementNodeSticky',
      'type' => 'sticky',
      'group' => 'Node',
    );
  }

  return $elements;
}
