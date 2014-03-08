<?php
/**
 * @file
 * Define Display plugin for the add page.
 */

/**
 * Class for add page displays.
 */
class FlexiformDisplayEditPage extends FlexiformDisplayPageBase {

  /**
   * Define the menu links
   */
  public function hook_menu() {
    $path_bits = explode('/', $this->configuration['path']);
    $wildcard_key = array_search('%', $path_bits);
    if ($wildcard_key === FALSE) {
      return;
    }

    $items = parent::hook_menu();

    foreach ($items as &$item) {
      $item['title arguments'][] = 'flexiform_edit_entity_page';
      $item['title arguments'][] = $wildcard_key;
      $item['page arguments'][] = 'flexiform_edit_entity_page';
      $item['page arguments'][] = $wildcard_key;
    }

    return $items;
  }

  /**
   * {@inheritdoc}
   */
  public function getBaseEntity($context = array()) {
    $base_entity = entity_load_single($this->flexiform->base_entity, $context['base_entity_id']);

    //@todo: Check the entity is the right bundle.
    return $base_entity;
  }

  /**
   * Get the configuration form.
   */
  public function configForm($form, &$form_state) {
    $form = parent::configForm($form, $form_state);

    $form['path']['#description'] = t('The path to this form. Must include a single \'%\' where the id of the base entity will go.');

    return $form;
  }
}
