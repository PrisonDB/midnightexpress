<?php
/**
 * @file
 * me_prisons.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function me_prisons_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "feeds_tamper" && $api == "feeds_tamper_default") {
    return array("version" => "2");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function me_prisons_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function me_prisons_default_search_api_index() {
  $items = array();
  $items['prisons'] = entity_import('search_api_index', '{
    "name" : "Prisons",
    "machine_name" : "prisons",
    "description" : null,
    "server" : "database",
    "item_type" : "taxonomy_term",
    "options" : {
      "index_directly" : 0,
      "cron_limit" : "50",
      "fields" : {
        "tid" : { "type" : "integer" },
        "name" : { "type" : "text" },
        "description" : { "type" : "text" },
        "url" : { "type" : "uri" },
        "vocabulary" : { "type" : "integer", "entity_type" : "taxonomy_vocabulary" },
        "field_security_level" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_email" : { "type" : "text" },
        "field_prison_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_prison_region" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_phone" : { "type" : "text" },
        "search_api_language" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "prison" : "prison" } }
        },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "mode" : "Taxonomy term page" }
        },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "name" : true,
              "description" : true,
              "field_email" : true,
              "field_phone" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "name" : true,
              "description" : true,
              "field_email" : true,
              "field_phone" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "name" : true,
              "description" : true,
              "field_email" : true,
              "field_phone" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "name" : true,
              "description" : true,
              "field_email" : true,
              "field_phone" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function me_prisons_default_search_api_server() {
  $items = array();
  $items['database'] = entity_import('search_api_server', '{
    "name" : "Database",
    "machine_name" : "database",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "1",
      "indexes" : { "prisons" : {
          "tid" : {
            "table" : "search_api_db_prisons",
            "column" : "tid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "name" : {
            "table" : "search_api_db_prisons_name",
            "type" : "text",
            "boost" : "1.0"
          },
          "description" : {
            "table" : "search_api_db_prisons_description",
            "type" : "text",
            "boost" : "1.0"
          },
          "url" : {
            "table" : "search_api_db_prisons",
            "column" : "url",
            "type" : "uri",
            "boost" : "1.0"
          },
          "field_security_level" : {
            "table" : "search_api_db_prisons",
            "column" : "field_security_level",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_email" : {
            "table" : "search_api_db_prisons_field_email",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_prison_type" : {
            "table" : "search_api_db_prisons",
            "column" : "field_prison_type",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_prison_region" : {
            "table" : "search_api_db_prisons",
            "column" : "field_prison_region",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_phone" : {
            "table" : "search_api_db_prisons_field_phone",
            "type" : "text",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_prisons",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "vocabulary" : {
            "table" : "search_api_db_prisons",
            "column" : "vocabulary",
            "type" : "integer",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
