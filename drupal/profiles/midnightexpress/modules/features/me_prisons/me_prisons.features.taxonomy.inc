<?php
/**
 * @file
 * me_prisons.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function me_prisons_taxonomy_default_vocabularies() {
  return array(
    'prison' => array(
      'name' => 'Prison',
      'machine_name' => 'prison',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'prison_region' => array(
      'name' => 'Prison Region',
      'machine_name' => 'prison_region',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'prison_type' => array(
      'name' => 'Prison Type',
      'machine_name' => 'prison_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'security_level' => array(
      'name' => 'Security Level',
      'machine_name' => 'security_level',
      'description' => 'Security level for a prison',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
