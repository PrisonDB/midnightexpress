<?php

/**
 * @file
 * Views for the default Commerce Card on File.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_cardonfile_views_default_views() {
  $views = array();

  // Stored cards: User
  $view = new view();
  $view->name = 'commerce_card_on_file_user_cards';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_cardonfile';
  $view->human_name = 'Stored cards: User';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stored cards';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view own card data';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'card_type' => 'card_type',
    'card_number' => 'card_number',
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'You have stored the following credit card(s) on file for this account. If you have any pending orders or recurring payments, please take great care when updating or deleting your card data.';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You do not have any stored credit cards on file for this account.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Commerce Card Data: Referenced customer profile */
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['id'] = 'commerce_cardonfile_profile_profile_id';
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['table'] = 'field_data_commerce_cardonfile_profile';
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['field'] = 'commerce_cardonfile_profile_profile_id';
  /* Field: Commerce Card on File: Card number */
  $handler->display->display_options['fields']['card_number']['id'] = 'card_number';
  $handler->display->display_options['fields']['card_number']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_number']['field'] = 'card_number';
  $handler->display->display_options['fields']['card_number']['label'] = '';
  $handler->display->display_options['fields']['card_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['card_number']['element_type'] = 'strong';
  $handler->display->display_options['fields']['card_number']['element_label_colon'] = FALSE;
  /* Field: Commerce Card on File: Card type */
  $handler->display->display_options['fields']['card_type']['id'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_type']['field'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['label'] = '';
  $handler->display->display_options['fields']['card_type']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['card_type']['alter']['text'] = '<strong>[card_type] ending in [card_number]</strong>';
  $handler->display->display_options['fields']['card_type']['element_label_colon'] = FALSE;
  /* Field: Commerce Card on File: Card expiration month */
  $handler->display->display_options['fields']['card_exp_month']['id'] = 'card_exp_month';
  $handler->display->display_options['fields']['card_exp_month']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_exp_month']['field'] = 'card_exp_month';
  $handler->display->display_options['fields']['card_exp_month']['exclude'] = TRUE;
  /* Field: Commerce Card on File: Card expiration year */
  $handler->display->display_options['fields']['card_exp_year']['id'] = 'card_exp_year';
  $handler->display->display_options['fields']['card_exp_year']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_exp_year']['field'] = 'card_exp_year';
  $handler->display->display_options['fields']['card_exp_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['card_exp_year']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Expires';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[card_exp_month] / [card_exp_year]';
  /* Field: Commerce Card on File: Name on the card */
  $handler->display->display_options['fields']['card_name']['id'] = 'card_name';
  $handler->display->display_options['fields']['card_name']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_name']['field'] = 'card_name';
  $handler->display->display_options['fields']['card_name']['label'] = 'Name';
  /* Field: Commerce Card Data: Billing Profile */
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['id'] = 'commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['table'] = 'field_data_commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['field'] = 'commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['label'] = 'Address';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_type'] = '0';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['field_api_classes'] = TRUE;
  /* Field: Commerce Card on File: Card data status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  /* Field: Commerce Card on File: Default card */
  $handler->display->display_options['fields']['instance_default']['id'] = 'instance_default';
  $handler->display->display_options['fields']['instance_default']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['instance_default']['field'] = 'instance_default';
  $handler->display->display_options['fields']['instance_default']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['instance_default']['type'] = 'custom';
  $handler->display->display_options['fields']['instance_default']['type_custom_true'] = 'Default card on file.';
  $handler->display->display_options['fields']['instance_default']['not'] = 0;
  /* Field: Commerce Card on File: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = '';
  $handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['operations']['add_destination'] = 1;
  /* Sort criterion: Commerce Card on File: Default card */
  $handler->display->display_options['sorts']['instance_default']['id'] = 'instance_default';
  $handler->display->display_options['sorts']['instance_default']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['sorts']['instance_default']['field'] = 'instance_default';
  $handler->display->display_options['sorts']['instance_default']['order'] = 'DESC';
  /* Sort criterion: Commerce Card on File: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Commerce Card on File: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'commerce_cof_owner';
  $handler->display->display_options['arguments']['uid']['validate']['fail'] = 'access denied';
  /* Filter criterion: Commerce Card on File: Card data status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
    3 => '3',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/cards';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Stored cards';
  $handler->display->display_options['menu']['description'] = 'Manage your stored card data.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['commerce_card_on_file_user_cards'] = array(
    t('Master'),
    t('Stored cards'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('You have stored the following credit card(s) on file for this account. If you have any pending orders or recurring payments, please take great care when updating or deleting your card data.'),
    t('You do not have any stored credit cards on file for this account.'),
    t('Customer profile referenced by commerce_cardonfile_profile'),
    t('<strong>[card_type] ending in [card_number]</strong>'),
    t('Card expiration month'),
    t('.'),
    t(','),
    t('Card expiration year'),
    t('Expires'),
    t('[card_exp_month] / [card_exp_year]'),
    t('Name'),
    t('Address'),
    t('Status'),
    t('Default card'),
    t('Default card on file.'),
    t('All'),
    t('Page'),
  );

  $views[$view->name] = $view;

  // Stored cards: Admin
  $view = new view();
  $view->name = 'commerce_card_on_file_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_cardonfile';
  $view->human_name = 'Stored cards: Admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stored Cards';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer card data';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'name' => 'name',
    'card_type' => 'card_type',
    'card_number' => 'card_type',
    'card_exp_month' => 'card_exp_month',
    'card_exp_year' => 'card_exp_year',
    'nothing' => 'nothing',
    'card_name' => 'card_name',
    'commerce_cardonfile_profile' => 'commerce_cardonfile_profile',
    'status' => 'status',
    'instance_default' => 'instance_default',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'card_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;ending&nbsp;in&nbsp;',
      'empty_column' => 0,
    ),
    'card_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'card_exp_month' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'card_exp_year' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'card_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'commerce_cardonfile_profile' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'instance_default' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'This table lists out all of the stored cards on file your customers have added to their accounts. Stored cards may be used by your customers for future purchases or in the processing of recurring payments, so take great care when you update or delete card data.';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No customers have stored a credit card on file yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Commerce Card Data: Referenced customer profile */
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['id'] = 'commerce_cardonfile_profile_profile_id';
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['table'] = 'field_data_commerce_cardonfile_profile';
  $handler->display->display_options['relationships']['commerce_cardonfile_profile_profile_id']['field'] = 'commerce_cardonfile_profile_profile_id';
  /* Relationship: Commerce Card on File: Owner */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Commerce Card on File: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Commerce Card on File: Card type */
  $handler->display->display_options['fields']['card_type']['id'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_type']['field'] = 'card_type';
  $handler->display->display_options['fields']['card_type']['label'] = 'Card';
  $handler->display->display_options['fields']['card_type']['element_label_colon'] = FALSE;
  /* Field: Commerce Card on File: Card number */
  $handler->display->display_options['fields']['card_number']['id'] = 'card_number';
  $handler->display->display_options['fields']['card_number']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_number']['field'] = 'card_number';
  $handler->display->display_options['fields']['card_number']['label'] = 'Ending';
  /* Field: Commerce Card on File: Card expiration month */
  $handler->display->display_options['fields']['card_exp_month']['id'] = 'card_exp_month';
  $handler->display->display_options['fields']['card_exp_month']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_exp_month']['field'] = 'card_exp_month';
  $handler->display->display_options['fields']['card_exp_month']['label'] = '';
  $handler->display->display_options['fields']['card_exp_month']['exclude'] = TRUE;
  $handler->display->display_options['fields']['card_exp_month']['element_label_colon'] = FALSE;
  /* Field: Commerce Card on File: Card expiration year */
  $handler->display->display_options['fields']['card_exp_year']['id'] = 'card_exp_year';
  $handler->display->display_options['fields']['card_exp_year']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_exp_year']['field'] = 'card_exp_year';
  $handler->display->display_options['fields']['card_exp_year']['label'] = '';
  $handler->display->display_options['fields']['card_exp_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['card_exp_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['card_exp_year']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Expires';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[card_exp_month] / [card_exp_year]';
  /* Field: Commerce Card on File: Name on the card */
  $handler->display->display_options['fields']['card_name']['id'] = 'card_name';
  $handler->display->display_options['fields']['card_name']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['card_name']['field'] = 'card_name';
  $handler->display->display_options['fields']['card_name']['label'] = 'Name';
  /* Field: Commerce Card Data: Billing Profile */
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['id'] = 'commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['table'] = 'field_data_commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['field'] = 'commerce_cardonfile_profile';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['label'] = 'Address';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_type'] = '0';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['commerce_cardonfile_profile']['field_api_classes'] = TRUE;
  /* Field: Commerce Card on File: Card data status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  /* Field: Commerce Card on File: Default card */
  $handler->display->display_options['fields']['instance_default']['id'] = 'instance_default';
  $handler->display->display_options['fields']['instance_default']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['instance_default']['field'] = 'instance_default';
  $handler->display->display_options['fields']['instance_default']['label'] = 'Default?';
  $handler->display->display_options['fields']['instance_default']['not'] = 0;
  /* Field: Commerce Card on File: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = 'Operations';
  $handler->display->display_options['fields']['operations']['add_destination'] = 0;
  /* Filter criterion: Commerce Card on File: Card data status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_cardonfile';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
    3 => '3',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/cards';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Stored cards';
  $handler->display->display_options['menu']['description'] = 'View and manage all of the stored credit cards on your site.';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['commerce_card_on_file_admin'] = array(
    t('Master'),
    t('Stored Cards'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('This table lists out all of the stored cards on file your customers have added to their accounts. Stored cards may be used by your customers for future purchases or in the processing of recurring payments, so take great care when you update or delete card data.'),
    t('No customers have stored a credit card on file yet.'),
    t('Customer profile referenced by commerce_cardonfile_profile'),
    t('Card owner'),
    t('Created'),
    t('User'),
    t('Card'),
    t('Ending'),
    t('.'),
    t(','),
    t('Expires'),
    t('[card_exp_month] / [card_exp_year]'),
    t('Name'),
    t('Address'),
    t('Status'),
    t('Default?'),
    t('Operations'),
    t('Page'),
  );

  $views[$view->name] = $view;

  return $views;
}
