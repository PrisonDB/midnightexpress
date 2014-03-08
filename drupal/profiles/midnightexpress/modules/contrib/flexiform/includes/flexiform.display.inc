<?php
/**
 * @file
 * Specify base display classes for flexiforms.
 */

/**
 * Interface for all display classes.
 */
interface FlexiformDisplayInterface {

  /**
   * Get the base entity for the flexible form.
   *
   * @param Flexiform $flexiform
   *   A flexiform object.
   * @param array $configuration
   *   The configration as stored in the flexiform.
   * @param array $context
   *   (optional) An array of settings and values to help the plugin return the
   *   entity.
   *
   * @return stdClass|Entity
   *   The base entity for the form.
   */
  public function getBaseEntity($context = array());

  /**
   * Build the form ready for rendering.
   */
  public function build($context = array());

  /**
   * Get the title for a built form.
   */
  public function title($context = array());

  /**
   * Get the config form.
   */
  public function configForm($form, &$form_state);
}

/**
 * Base class for all flexiform displays.
 */
class FlexiformDisplayBase implements FlexiformDisplayInterface {

  public function __construct(Flexiform $flexiform, array $configuration = array()) {
    $this->flexiform = $flexiform;
    $this->configuration = $configuration;
  }

  /**
   * Get the base entity for a flexiform.
   *
   * By default we just create a new entity.
   */
  public function getBaseEntity($context = array()) {
    $info = entity_get_info($this->flexiform->base_entity);
    $values = array();

    if (!empty($info['entity keys']['bundle'])) {
      $values[$info['entity keys']['bundle']] = $this->flexiform->base_entity_bundle;
    }

    $base_entity = entity_create($this->flexiform->base_entity, $values);
    return $base_entity;
  }

  /**
   * Is this display enabled.
   */
  public function isEnabled() {
    return !empty($this->configuration['enabled']);
  }

  /**
   * Build the form ready for rendering.
   */
  public function build($context = array()) {
    module_load_include('inc', 'flexiform', 'includes/flexiform.flexiform');
    $base_entity = $this->getBaseEntity($context);
    return flexiform_wrapper($this->flexiform, $base_entity);
  }

  /**
   * Get the title.
   */
  public function title($context = array()) {
    return $this->flexiform->label;
  }

  /**
   * Build the config form.
   */
  public function configForm($form, &$form_state) {
    $form['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Enabled',
      '#default_value' => !empty($this->configuration['enabled']),
    );

    $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => !empty($this->configuration['title']) ? $this->configuration['title'] : '',
    );

    return $form;
  }

}
