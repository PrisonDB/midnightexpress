<?php

/**
 * Class bitcoinClient
 *
 * Ultra thin wrapper to jsonRPCClient
 *
 */
class bitcoinClient extends jsonRPCClient {


  /**
   * Takes the connection parameters
   *
   * @param string $url
   * @param boolean $debug
   */
  public function __construct($url, $debug = false) {
    parent::__construct($url, $debug);
  }

  function testConnection() {
    $info = FALSE;

    try {
      $info = $this->getinfo();
    } catch (Exception $e) {
      return false;
    }
    return $info;
  }

  /**
   * Determine if a string is a valid Bitcoin address
   *
   * @author theymos
   * @param string $addr String to test
   * @param string $addressversion
   * @return boolean
   * @access public
   */
  public static function checkAddress($addr, $addressversion = BITCOIN_ADDRESS_VERSION) {
    $addr = self::decodeBase58($addr);
    if (strlen($addr) != 50) {
      return false;
    }
    $version = substr($addr, 0, 2);
    if (hexdec($version) > hexdec($addressversion)) {
      return false;
    }
    $check = substr($addr, 0, strlen($addr) - 8);
    $check = pack("H*", $check);
    $check = strtoupper(hash("sha256", hash("sha256", $check, true)));
    $check = substr($check, 0, 8);
    return $check == substr($addr, strlen($addr) - 8);
  }

}