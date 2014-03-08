<?php
/**
 * @file
 * Base definition for pages.
 */

/**
 * Base class for page displays.
 */
abstract class FlexiformDisplayPageBase extends FlexiformDisplayBase {

  /**
   * Define the menu links
   */
  public function hook_menu() {
    $items = array();

    $items[$this->configuration['path']] = array(
      'title callback' => 'flexiform_page_title',
      'title arguments' => array($this->flexiform->form),
      'page callback' => 'flexiform_page_wrapper',
      'page arguments' => array($this->flexiform->form),
      'access callback' => TRUE,
      'file' => 'flexiform.pages.inc',
    );

    // Add the menu name if we have one.
    if (isset($this->configuration['menu_name'])) {
      $items[$this->configuration['path']]['menu_name'] = $this->configuration['menu_name'];
    }

    // Add the type if we have one.
    if (isset($this->configuration['type'])) {
      $items[$this->configuration['path']]['type'] = $this->configuration['type'];

      // @TODO: Deal properly with default local tasks.
    }

    return $items;
  }

  /**
   * Get the configuration form.
   */
  public function configForm($form, &$form_state) {
    $form = parent::configForm($form, $form_state);

    $form['path'] = array(
      '#title' => t('Path'),
      '#type' => 'textfield',
      '#default_value' => isset($this->configuration['path']) ? $this->configuration['path'] : NULL,
    );

    $form['type'] = array(
      '#title' => t('Menu type'),
      '#type' => 'select',
      '#description' => t('Select the type of menu item to use.'),
      '#options' => array(
        MENU_CALLBACK => t('No menu item'),
        MENU_NORMAL_ITEM => t('Normal menu item'),
        MENU_LOCAL_ACTION => t('Local action'),
        MENU_LOCAL_TASK => t('Tab'),
        MENU_DEFAULT_LOCAL_TASK => t('Default tab'),
      ),
      '#default_value' => isset($this->configuration['type']) ? $this->configuration['type'] : MENU_CALLBACK,
    );

    $form['menu_name'] = array(
      '#title' => t('Menu'),
      '#type' => 'select',
      '#description' => t('Select the menu the item should be put in.'),
      '#options' => menu_get_menus(),
      '#default_value' => isset($this->configuration['menu_name']) ? $this->configuration['menu_name'] : NULL,
      '#states' => array(
        'visible' => array(':input[name="displays[flexiform_create_entity_page][type]"]' => array('!value' => MENU_CALLBACK)),
      ),
    );

    return $form;
  }

  /**
   * Get the title.
   */
  public function title($context = array()) {
    return $this->configuration['title'];
  }
}
