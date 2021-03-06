<?php
/**
 * @file
 * Party Activity editing UI
 */

/**
 * UI Controller
 */
class PartyActivityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that parent
   * class hook_menu is optimized for entity type administration.
   */
  public function hook_menu() {
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Activities',
      'description' => 'Add edit and update activities.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Change the overview menu type for the list of activities.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add an activity',
      'description' => 'Add a new activity',
      'page callback'  => 'party_activity_add_page',
      'access callback'  => 'party_activity_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'party_activity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );

    // Add menu items to add each different type of entity.
    foreach (party_activity_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'party_activity_form_wrapper',
        'page arguments' => array(party_activity_create(array('type' => $type->type))),
        'access callback' => 'party_activity_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'party_activity.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing party_activity entities
    $items[$this->path . '/activity/' . $wildcard] = array(
      'title callback' => 'party_activity_page_title',
      'title arguments' => array($id_count + 1, 'edit'),
      'page callback' => 'party_activity_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'party_activity_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'party_activity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/activity/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/activity/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'party_activity_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'party_activity_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'party_activity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing party activity
    $items['activity/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'party_activity_page_title',
      'title arguments' => array(1),
      'page callback' => 'party_activity_page_view',
      'page arguments' => array(1),
      'access callback' => 'party_activity_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }

  /**
   * Create the markup for the add Party Activity Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('party_activity_add_list', array('content' => $content));
  }
}

/**
 * Form callback wrapper: create or edit a activity.
 *
 * @param $activity
 *   The PartyActivity object being edited by this form.
 *
 * @see party_activity_edit_form()
 */
function party_activity_form_wrapper($activity) {
  // Add the breadcrumb for the form's location.
  party_activity_set_breadcrumb();
  // If its a new activity we can take arguments from the URL to make it quicker to assign
  if (!empty($activity->is_new) && $activity->is_new) {
    $assignee = !empty($_GET['assignee']) ? $_GET['assignee'] : NULL;
    $participants = !empty($_GET['participants']) ? explode(',', $_GET['participants']) : array();
    if (!empty($assignee)) {
      $activity->activity_assigned_to['und'][]['target_id'] = $assignee;
    }

    foreach ($participants as $participant_id) {
      $activity->activity_participants['und'][]['target_id'] = $participant_id;
    }
  }

  return drupal_get_form('party_activity_edit_form', $activity);
}

/**
 * Form callback wrapper: delete a party activity.
 *
 * @param $activity
 *   The activity object being edited by this form.
 *
 * @see party_activity_edit_form()
 */
function party_activity_delete_form_wrapper($activity) {
  // Add the breadcrumb for the form's location.
  //activity_set_breadcrumb();
  return drupal_get_form('party_activity_delete_form', $activity);
}


/**
 * Form callback: create or edit a activity.
 *
 * @param $activity
 *   The PartyActivity object to edit or for a create form fot an empty
 *   PartyActivity object with only a type defined.
 */
function party_activity_edit_form($form, &$form_state, $activity) {
  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($activity->title) ? $activity->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['party_activity'] = $activity;
  field_attach_form('party_activity', $activity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('party_activity_edit_form_submit'),
  );

  if (!empty($activity->party_activity_id)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#suffix' => l(t('Cancel'), 'admin/community/activities'),
      '#submit' => $submit + array('party_activity_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'party_activity_edit_form_validate';
  return $form;
}

/**
 * Form API validate callback for the party_activity form
 */
function party_activity_edit_form_validate(&$form, &$form_state) {
  $activity = $form_state['party_activity'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('party_activity', $activity, $form, $form_state);
}

/**
 * Form API submit callback for the activity form.
 *
 * @todo remove hard-coded link
 */
function party_activity_edit_form_submit(&$form, &$form_state) {

  $activity = entity_ui_controller('party_activity')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the activity and go back to the list of activities

  // Add in created and changed times.
  if ($activity->is_new = isset($activity->is_new) ? $activity->is_new : 0) {
    $activity->created = time();
  }

  $activity->modified = time();

  $activity->save();
  $form_state['redirect'] = 'admin/community/activities';
}

/**
 * Form API submit callback for the delete button.
 *
 * @todo Remove hard-coded path
 */
function party_activity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/community/activitiess/activity/' . $form_state['activity']->party_activity_id . '/delete';
}

/**
 * Form callback: confirmation form for deleting a activity.
 *
 * @param $activity
 *   The party_activity to delete
 *
 * @see confirm_form()
 */
function party_activity_delete_form($form, &$form_state, $activity) {
  $form_state['activity'] = $activity;

  $form['#submit'][] = 'party_activity_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete activity %title?', array('%title' => $activity->title)),
    'admin/community/activities/activity',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for activity_delete_form
 */
function party_activity_delete_form_submit($form, &$form_state) {
  $activity = $form_state['activity'];

  party_activity_delete($activity);

  drupal_set_message(t('The activity %title has been deleted.', array('%title' => $activity->title)));
  watchdog('activity', 'Deleted activity %title.', array('%title' => $activity->title));

  $form_state['redirect'] = 'admin/community/activities';
}

/**
 * Page to add activity Entities.
 *
 * @todo Pass this through a proper theme function
 */
function party_activity_add_page() {
  $controller = entity_ui_controller('party_activity');
  return $controller->addPage();
}

/**
 * Displays the list of available activity types for activity creation.
 *
 * @ingroup themeable
 */
function theme_party_activity_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="party-activity-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer party activity types')) {
      $output = '<p>' . t('Party Activity Entities cannot be added because you have not created any party activity types yet. Go to the <a href="@create-activity-type">activity type creation page</a> to add a new activity type.', array('@create-activity-type' => url('admin/structure/party_activity_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No activity types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative activity pages.
 */
function party_activity_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Community'), 'admin/community'),
    l(t('Activities'), 'admin/community/activities'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
