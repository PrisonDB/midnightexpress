<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */

class party_activity_handler_edit_link_field extends party_activity_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['party_activity_id'] = 'party_activity_id';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};

    //Creating a dummy model to check access against
    $dummy_activity = (object) array('type' => $type);
    if (!party_activity_access('edit', $dummy_activity)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $activity_id = $values->{$this->aliases['party_activity_id']};

    return l($text, 'admin/community/activities/activity/' . $activity_id . '/edit');
  }
}
