<?php
/**
 * @file
 * Rules integration for the flexiform module.
 */

/**
 * Implements hook_rules_event_info().
 */
function flexiform_rules_event_info() {
  $defaults = array(
    'group' => t('Flexiform'),
    'module' => 'flexiform',
  );

  $events = array();
  foreach(entity_load('flexiform') as $flexiform) {
    $event = $defaults + array(
      'label' => t('On submitting @flexiform', array('@flexiform' => $flexiform->label)),
      'variables' => array(),
    );

    foreach ($flexiform->entities as $entity_namespace => $settings) {
      $variable = array(
        'type' => $settings['entity_type'],
        'label' => $settings['label'],
      );
      $event['variables'][$entity_namespace] = $variable;
    }

    $events['flexiform_submit_'. $flexiform->form] = $event;
  }

  return $events;
}
