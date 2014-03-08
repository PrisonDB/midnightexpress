<?php
/**
 * @file
 * Contains class for the Node title element.
 */

/**
 * Class to add the node title field to a form.
 */
class FlexiformElementNodeTitle extends FlexiformElement {

  /**
   * Return the form element for this FlexiformElement.
   */
  public function form($form, &$form_state, $entity, $language = LANGUAGE_NONE) {
    $parents = $form['#parents'];
    $parents[] = 'title';

    $form[$this->element_namespace] = array(
      '#type' => 'textfield',
      '#parents' => $parents,
      '#title' => $this->label(),
      '#required' => TRUE,
      '#default_value' => !empty($entity->title) ? $entity->title : '',
      '#maxlength' => 255,
    );

    $form = parent::form($form, $form_state, $entity);

    return $form;
  }

  /**
   * Validate the form element.
   */
  public function formValidate($form, &$form_state, $entity, $language = LANGUAGE_NONE) {
  }

  /**
   * Submit the form element.
   */
  public function formSubmit($form, &$form_state, $entity, $language = LANGUAGE_NONE) {
    $title = $this->formExtractValues($form, $form_state, $entity);
    $entity->title = $title;
  }

  /**
   * Extract the submitted values for this form element.
   */
  public function formExtractValues($form, &$form_state, $entity) {
    $parents = $form['#parents'];
    $parents[] = $this->getEntityNamespace();
    $parents[] = 'title';

    $title = drupal_array_get_nested_value($form_state['values'], $parents);
    return $title;
  }
}
