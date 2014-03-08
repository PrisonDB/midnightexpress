<?php
/**
 * @file
 * me_prisons.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function me_prisons_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'prison_importer';
  $feeds_importer->config = array(
    'name' => 'Prison Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.Locations.*',
        'sources' => array(
          'jsonpath_parser:0' => 'code',
          'jsonpath_parser:1' => 'contactEmail',
          'jsonpath_parser:2' => 'url',
          'jsonpath_parser:3' => 'latitude',
          'jsonpath_parser:4' => 'longitude',
          'jsonpath_parser:5' => 'securityLevel',
          'jsonpath_parser:6' => 'nameDisplay',
          'jsonpath_parser:7' => 'faclTypeDescription',
          'jsonpath_parser:9' => '',
          'jsonpath_parser:10' => 'zipCode',
          'jsonpath_parser:11' => 'city',
          'jsonpath_parser:12' => '',
          'jsonpath_parser:13' => 'state',
          'jsonpath_parser:15' => 'region',
          'jsonpath_parser:16' => 'address',
          'jsonpath_parser:18' => 'phoneNumber',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:10' => 0,
            'jsonpath_parser:11' => 0,
            'jsonpath_parser:12' => 0,
            'jsonpath_parser:13' => 0,
            'jsonpath_parser:15' => 0,
            'jsonpath_parser:16' => 0,
            'jsonpath_parser:18' => 0,
          ),
        ),
        'allow_override' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'field_email',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_website:url',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_location:lat',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_location:lon',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_security_level',
            'term_search' => '0',
            'autocreate' => 1,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'name',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_prison_type',
            'term_search' => '0',
            'autocreate' => 1,
          ),
          8 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_address:country',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:10',
            'target' => 'field_address:postal_code',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:11',
            'target' => 'field_address:locality',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'field_address:premise',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:13',
            'target' => 'field_address:administrative_area',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'jsonpath_parser:15',
            'target' => 'field_prison_region',
            'term_search' => '0',
            'autocreate' => 1,
          ),
          14 => array(
            'source' => 'jsonpath_parser:16',
            'target' => 'field_address:thoroughfare',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'jsonpath_parser:18',
            'target' => 'field_phone',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'prison',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['prison_importer'] = $feeds_importer;

  return $export;
}
