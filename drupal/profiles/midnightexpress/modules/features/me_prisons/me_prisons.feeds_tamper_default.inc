<?php
/**
 * @file
 * me_prisons.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function me_prisons_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-jsonpath_parser_11-convert_case';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'jsonpath_parser:11';
  $feeds_tamper->plugin_id = 'convert_case';
  $feeds_tamper->settings = array(
    'mode' => '2',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert case';
  $export['prison_importer-jsonpath_parser_11-convert_case'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-jsonpath_parser_16-convert_case';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'jsonpath_parser:16';
  $feeds_tamper->plugin_id = 'convert_case';
  $feeds_tamper->settings = array(
    'mode' => '2',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert case';
  $export['prison_importer-jsonpath_parser_16-convert_case'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-jsonpath_parser_2-str_pad';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'jsonpath_parser:2';
  $feeds_tamper->plugin_id = 'str_pad';
  $feeds_tamper->settings = array(
    'pad_length' => 18,
    'pad_string' => 'http://www.bop.gov',
    'pad_type' => '0',
    'real_pad_string' => 'http://www.bop.gov',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Pad a string';
  $export['prison_importer-jsonpath_parser_2-str_pad'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-jsonpath_parser_8-str_pad';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'jsonpath_parser:8';
  $feeds_tamper->plugin_id = 'str_pad';
  $feeds_tamper->settings = array(
    'pad_length' => 18,
    'pad_string' => 'http://www.bop.gov',
    'pad_type' => '0',
    'real_pad_string' => 'http://www.bop.gov',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Pad a string';
  $export['prison_importer-jsonpath_parser_8-str_pad'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-jsonpath_parser_9-default_value';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'jsonpath_parser:9';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'US',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default value';
  $export['prison_importer-jsonpath_parser_9-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-xpathparser_10-str_pad';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'xpathparser:10';
  $feeds_tamper->plugin_id = 'str_pad';
  $feeds_tamper->settings = array(
    'pad_length' => 18,
    'pad_string' => 'http://www.bop.gov',
    'pad_type' => '0',
    'real_pad_string' => 'http://www.bop.gov',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Append bop url';
  $export['prison_importer-xpathparser_10-str_pad'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-xpathparser_3-default_value';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'xpathparser:3';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'US',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Default Country';
  $export['prison_importer-xpathparser_3-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-xpathparser_6-convert_case';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'xpathparser:6';
  $feeds_tamper->plugin_id = 'convert_case';
  $feeds_tamper->settings = array(
    'mode' => '2',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'City Case';
  $export['prison_importer-xpathparser_6-convert_case'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'prison_importer-xpathparser_7-convert_case';
  $feeds_tamper->importer = 'prison_importer';
  $feeds_tamper->source = 'xpathparser:7';
  $feeds_tamper->plugin_id = 'convert_case';
  $feeds_tamper->settings = array(
    'mode' => '2',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Address Case';
  $export['prison_importer-xpathparser_7-convert_case'] = $feeds_tamper;

  return $export;
}
