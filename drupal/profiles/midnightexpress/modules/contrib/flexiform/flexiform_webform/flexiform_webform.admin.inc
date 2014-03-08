<?php
/**
 * @file
 * Model type editing UI.
 */

/**
 * UI Class
 */
class FlexiformWebformUIController extends EntityDefaultUIController {

  /**
   * {@inheritdoc}
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    // Change the way they clone things.
    $items['admin/structure/flexiform_webforms/manage/%entity_object/clone']['page callback'] = 'flexiform_webform_ui_get_clone_form';

    return $items;
  }

}

/**
 * Generates the model type editing form.
 */
function flexiform_webform_form($form, &$form_state, $webform, $op = 'edit') {
  if ($op == 'clone') {
    $webform->label .= ' (cloned)';
    $webform->webform = '';
  }

  $form['#op'] = $op;

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $webform->label,
    '#description' => t('The human-readable name of this webform.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['webform'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($webform->webform) ? $webform->webform : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'flexiform_webform_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this webform. It must only contain lowercase letters, numbers, and underscores.'),
    '#disabled' => empty($webform->is_new),
  );


  $form['cloned_from'] = array(
    '#type' => 'value',
    '#value' => !empty($webform->cloned_from) ? $webform->cloned_from : NULL,
  );

  $form['clone_fields'] = array(
    '#type' => 'checkbox',
    '#title' => t('Copy Field Definitions'),
    '#description' => t('This will copy the field instance settings from the original webform.'),
    '#default_value' => FALSE,
    '#access' => ($op == 'clone'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function flexiform_webform_form_submit(&$form, &$form_state) {
  $webform = entity_ui_form_submit_build_entity($form, $form_state);
  $webform->save();

  if (!empty($form_state['values']['clone_fields'])) {
    $original = $form_state['values']['cloned_from'];
    foreach (field_info_instances('flexiform_webform_submission', $original) as $instance) {
      $instance['bundle'] = $webform->webform;
      if (!field_info_instance('flexiform_webform_submission', $instance['field_name'], $webform->webform)) {
        field_create_instance($instance);
      }
    }
  }
  $form_state['redirect'] = 'admin/structure/flexiform_webforms';
}

/**
 * Form API submit callback for the delete button.
 */
function flexiform_webform_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/flexiform_webforms/manage/' . $form_state['webform']->webform . '/delete';
}
