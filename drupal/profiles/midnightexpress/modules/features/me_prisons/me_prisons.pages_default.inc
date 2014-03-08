<?php
/**
 * @file
 * me_prisons.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function me_prisons_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'prisons';
  $page->task = 'page';
  $page->admin_title = 'Prisons';
  $page->admin_description = '';
  $page->path = 'prisons';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_prisons_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'prisons';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'bootopoly_bryant';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'sidebar' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'All The F\'in Prisons';
  $display->uuid = '50003995-0fea-4257-a70d-e27eaec96b98';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-235c1b56-3eaa-4202-837d-b5e476023b02';
    $pane->panel = 'contentmain';
    $pane->type = 'views_panes';
    $pane->subtype = 'prisons-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '235c1b56-3eaa-4202-837d-b5e476023b02';
    $display->content['new-235c1b56-3eaa-4202-837d-b5e476023b02'] = $pane;
    $display->panels['contentmain'][0] = 'new-235c1b56-3eaa-4202-837d-b5e476023b02';
    $pane = new stdClass();
    $pane->pid = 'new-ac1e8a7d-107e-4db4-b7bb-7ebfaa1637b3';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-F7qYm7QTzC1FlElAHatcVmdkGH2cF0XJ';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Region',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'use_title' => 1,
        'use_footer' => 0,
        'panel_body' => 0,
        'footer_content' => '',
        'context_class' => 'panel-default',
      ),
      'style' => 'bootstrap_panel',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ac1e8a7d-107e-4db4-b7bb-7ebfaa1637b3';
    $display->content['new-ac1e8a7d-107e-4db4-b7bb-7ebfaa1637b3'] = $pane;
    $display->panels['sidebar'][0] = 'new-ac1e8a7d-107e-4db4-b7bb-7ebfaa1637b3';
    $pane = new stdClass();
    $pane->pid = 'new-90e3e5b4-f5be-412d-a34e-1a6859835ad3';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-7BwF3mowk9IMZGBCb8Rf1VpIglxDiDph';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Security Level',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'use_title' => 1,
        'use_footer' => 0,
        'panel_body' => 0,
        'footer_content' => '',
        'context_class' => 'panel-default',
      ),
      'style' => 'bootstrap_panel',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '90e3e5b4-f5be-412d-a34e-1a6859835ad3';
    $display->content['new-90e3e5b4-f5be-412d-a34e-1a6859835ad3'] = $pane;
    $display->panels['sidebar'][1] = 'new-90e3e5b4-f5be-412d-a34e-1a6859835ad3';
    $pane = new stdClass();
    $pane->pid = 'new-d551c2ab-6067-48f7-b249-d44b136038aa';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-UaCZULmhUYhr6i707ljfMabzYT8sZK1g';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Prison Type',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'use_title' => 1,
        'use_footer' => 0,
        'panel_body' => 0,
        'footer_content' => '',
        'context_class' => 'panel-default',
      ),
      'style' => 'bootstrap_panel',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'd551c2ab-6067-48f7-b249-d44b136038aa';
    $display->content['new-d551c2ab-6067-48f7-b249-d44b136038aa'] = $pane;
    $display->panels['sidebar'][2] = 'new-d551c2ab-6067-48f7-b249-d44b136038aa';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-235c1b56-3eaa-4202-837d-b5e476023b02';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['prisons'] = $page;

  return $pages;

}
