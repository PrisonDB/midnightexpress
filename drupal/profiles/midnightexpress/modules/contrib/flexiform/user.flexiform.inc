<?php
/**
 * @file entity getters and setters for the user entity
 */

/**
 * Simple entity getter for the current user.
 *
 * Note that if the user is logged out the function returns false. If an entity
 * getter returns false, flexiform might create a new instance of it.
 */
function flexiform_entity_getter_user_current_user($flexiform, $base_entity, $entities, $namespace, $config) {
  global $user;

  if ($user->uid == 0) {
    return FALSE;
  }

  return user_load($user->uid);
}

/**
 * Simple entity setter for the current user.
 */
function flexiform_entity_setter_user_current_user($flexiform, $base_entity, $entity, $entity_type, $entities, $namespace, $config) {
  entity_save($entity_type, $entity);
}
