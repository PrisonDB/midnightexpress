<?php

/**
 * @file
 * Contains class for the Custom HTML form element.
 */
class FlexiformElementCustomHtml extends FlexiformRepeatableElement {

  /**
   * Returns the custom html that is defined in the configure form.
   */
  public function form($form, &$form_state, $entity) {
    $parents = $form['#parents'];
    $parents[] = 'custom_html';

    $value = $form['#flexiform']->elements[$this->getElementNamespace()]['custom_html']['value'];
    $format = $form['#flexiform']->elements[$this->getElementNamespace()]['custom_html']['format'];

    // Perform some keyword substitution.
    $value = $this->replaceCtoolsSubstitutions($value, $form['#flexiform_entities']);

    $form[$this->element_namespace] = array(
      '#markup' => check_markup($value, $format),
      '#parents' => $parents,
    );

    $form = parent::form($form, $form_state, $entity);

    return $form;
  }

  /**
   * Builds the configuration form for the form element.
   */
  public function configureForm($form, &$form_state, $flexiform) {
    $form['custom_html'] = array(
      '#type' => 'text_format',
      '#title' => $this->label(),
      '#format' => !empty($this->settings['custom_html']['format']) ? $this->settings['custom_html']['format'] : NULL,
      '#default_value' => !empty($this->settings['custom_html']['value']) ? $this->settings['custom_html']['value'] : '',
    );

    $form['contexts'] = array(
      '#title' => t('Substitutions'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['contexts']['contexts'] = $this->getCtoolsSubstitutionsList();

    $form = parent::configureForm($form, $form_state, $flexiform);

    return $form;
  }

  /**
   * Validate the form element.
   */
  public function configureFormValidate($form, &$form_state, $flexiform) {
    parent::configureFormValidate($form, $form_state, $flexiform);
  }

  /**
   * Submit the form element.
   */
  public function configureFormSubmit($form, &$form_state, $flexiform) {
    $this->settings['custom_html'] = $form_state['values']['custom_html'];

    parent::configureFormSubmit($form, $form_state, $flexiform);
  }

  /**
   * Adds custom html to the settings array.
   *
   * @return array $settings
   *   The settings to be saved for the form element.
   */
  public function toSettingsArray() {
    $settings = parent::toSettingsArray();
    $settings['custom_html'] = $this->settings['custom_html'];

    return $settings;
  }

  /**
   * Get an array of ctools context for the flexiform.
   *
   * @param array $entities
   *   An array of entities keyed by namespace. If NULL, placeholder contexts
   *   will be used.
   *
   * @return ctools_context[]
   *   An array of ctools contexts.
   */
  public function getCtoolsContexts($entities = array()) {
    global $user;

    ctools_include('context');
    $contexts = array(
      'current-user' => ctools_context_create('entity:user', $user),
    );
    $contexts['current-user']->keyword = 'current-user';
    $contexts['current-user']->identifier = t('Logged-in user');
    foreach ($this->flexiform->entities as $namespace => $info) {
      $type = 'entity:' . $info['entity_type'];
      if (isset($entities[$namespace])) {
        $contexts[$namespace] = ctools_context_create($type, $entities[$namespace]);
      }
      else {
        $contexts[$namespace] = ctools_context_create_empty($type);
      }
      $contexts[$namespace]->keyword = $namespace;
      $contexts[$namespace]->identifier = $info['label'];
    }

    return $contexts;
  }

  /**
   * Replace ctools substitutions with their values.
   *
   * @param string $string
   *   The string we want to replace in.
   * @param array $entities
   *   An array of entities keyed by namespace. If NULL, placeholder contexts
   *   will be used.
   * @param array $keywords
   *   Optionally provide additional keywords to replace.
   *
   * @return string
   *   $string with it's substitutions replaced.
   */
  public function replaceCtoolsSubstitutions($string, $entities, $keywords = array()) {
    $contexts = $this->getCtoolsContexts($entities);
    return ctools_context_keyword_substitute($string, $keywords, $contexts);
  }

  /**
   * Build a list of possible ctools substitutions.
   *
   * @param array $keywords
   *   Optionally provide additional keywords to show.
   *
   * @return array
   *   A render array of substitutions.
   */
  public function getCtoolsSubstitutionsList($keywords = array()) {
    $content = array(
      '#theme' => 'table',
      '#header' => array(t('Keyword'), t('Value')),
      '#rows' => array(),
    );

    foreach ($this->getCtoolsContexts() as $context) {
      foreach (ctools_context_get_converters('%' . check_plain($context->keyword) . ':', $context) as $keyword => $title) {
        $content['#rows'][] = array(
          check_plain($keyword),
          t('@identifier: @title', array('@title' => $title, '@identifier' => $context->identifier)),
        );
      }
    }

    if (count($content['#rows'])) {
      return $content;
    }
    else {
      return array();
    }
  }
}
