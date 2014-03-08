<?php
/**
 * @file flexiform.entity.inc
 *
 * Entity class and controller for the flexiform entity
 */

/**
 * The class used for flexiform entities
 */
class Flexiform extends Entity {

  public $form;
  public $label;
  public $elements = array();
  public $entities = array();
  public $displays = array();

  public function __construct($values = array()) {
    parent::__construct($values, 'flexiform');
  }

  public function getBuilder($base_entity) {
    $builder = flexiform_builder_info($this->builder);
    $class_name = $builder['class'];

    if (!class_exists($class_name)) {
      throw new Exception('Builder class does not exist!');
    }

    return new $class_name($this, $base_entity);
  }

  public function getDisplay($display) {
    if (empty($this->displays[$display])) {
      return FALSE;
    }

    $display_info = flexiform_display_info($display);
    if (empty($display_info)) {
      drupal_set_message(t('Display plugin @plugin not found.', array('@plugin' => $display)), 'error');
      return new FlexiformDisplayNull($this, $this->displays[$display]);
    }

    $class_name = $display_info['class'];
    if (!class_exists($class_name)) {
      throw new Exception('Display class does not exist.');
    }

    return new $class_name($this, $this->displays[$display]);
  }

  public function createDisplay($display) {
    $display_info = flexiform_display_info($display);
    if (empty($display_info)) {
      drupal_set_message(t('Display plugin @plugin not found.', array('@plugin' => $display)), 'error');
      return new FlexiformDisplayNull($this, $this->displays[$display]);
    }

    $class_name = $display_info['class'];
    if (!class_exists($class_name)) {
      throw new Exception('Display class does not exist.');
    }

    return new $class_name($this);
  }

  public function addElement($element) {
    $this->elements[$element->getElementNamespace()] = $element->toSettingsArray();
  }

  public function removeElement($element) {
    unset($this->elements[$element->getElementNamespace()]);
  }

  public function updateElement($element) {
    $this->elements[$element->getElementNamespace()] = $element->toSettingsArray();
  }
}

/**
 * The Controller for FlexiformSubmission entities
 */
class FlexiformController extends EntityAPIControllerExportable {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

   /**
   * Create a flexiform - we first set up the values that are specific
   * to our flexiform schema but then also go through the EntityAPIController
   * function.
   *
   * @param $type
   *   The machine-readable type of the flexiform_submission.
   *
   * @return
   *   A flexiform object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our FlexiformSubmission
    $values += array(
      'id' => '',
      'is_new' => TRUE,
    );
    $flexiform = parent::create($values);

    return $flexiform;
  }

  /**
   * Overrides EntityAPIController::invoke().
   */
  public function invoke($hook, $entity) {
    parent::invoke($hook, $entity);

    if ($hook == 'insert' || $hook == 'update') {
      // Get hold of the display info.
      $display_info = flexiform_display_info();

      // Check for any displays implementing hook_menu.
      foreach ($entity->displays as $id => $display) {
        if (method_exists($display_info[$id]['class'], 'hook_menu')) {
          if ($hook == 'update') {
            // If the config has changed continue.
            if (isset($entity->original->displays[$id]) && $display == $entity->original->displays[$id]) {
              continue;
            }
          }

          // Mark the menu to be rebuilt.
          variable_set('menu_rebuild_needed', TRUE);
          break;
        }
      }
    }
  }
}
