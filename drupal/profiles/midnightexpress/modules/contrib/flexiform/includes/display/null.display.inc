<?php
/**
 * @file
 * Define Display plugin for if the plugin doesnt exist
 */

/**
 * Class for null displays.
 */
class FlexiformDisplayNull extends FlexiformDisplayBase {

  /**
   * Build the form ready for rendering.
   */
  public function build($context = array()) {
    return array();
  }
}
