<?php
/**
 * @file Entity and Controller classes for the Party Activity entity
 */

/**
 * The class used for Party Activity Entities
 */
class PartyActivity extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'party_activity');
  }

  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'activity/' . $this->party_activity_id);
  }

}

/**
 * The controller class for Party Activities
 */
class PartyActivityController extends EntityAPIController {

  /**
   * Create a PartyActivity - we first set up the values that are specific to
   * our party_activity schema
   */
  public function create(array $values = array()) {
    $values += array(
      'party_activity_id' => '',
      'is_new' => TRUE,
      'title' => '',
      'created' => REQUEST_TIME,
      'modified' => REQUEST_TIME,
    );

    $activity = parent::create($values);
    return $activity;
  }
}
