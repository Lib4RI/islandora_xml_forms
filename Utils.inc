<?php

// $Id$

/**
 * @file
 *
 */

/**
 * A class of static helper methods.
 */
class Utils {

  public static function convertNodeToPath(DOMNode &$node) {
    $node = self::getXPathToNode($node);
  }

  public static function getXPathToNode(DOMNode $node) {
    $path = self::getXPathDOMNodeFragment($node);
    while (($node = $node->parentNode) && get_class($node) == 'DOMElement') {
      $name = self::getXPathDOMNodeFragment($node);
      $path = "$name/$path";
    }
    return "/$path";
  }

  public static function getChildNodeXPathIndex(DOMNode $parent, DOMNode $child) {
    $xpath = new DOMXPath($child->ownerDocument);
    $results = $xpath->query('child::*', $parent);
    $count = $results->length;
    $index = 1;
    for ($i = 0; $i < $count; $i++) {
      $node = $results->item($i);
      if ($child->isSameNode($node)) {
        break;
      }
      $index++;
    }
    return $index;
  }

  public static function getXPathDOMNodeFragment(DOMNode $node) {
    if (get_class($node) == 'DOMAttr') {
      return "@{$node->nodeName}";
    }
    else {
      $index = self::getChildNodeXPathIndex($node->parentNode, $node);
      return "{$node->nodeName}[$index]";
    }
  }

  public static function getDrupalFormElement($hash, array &$form) {
    $iterator = new RecursiveIteratorIterator(new RecursiveArrayIterator($form), RecursiveIteratorIterator::SELF_FIRST);
    foreach ($iterator as $element) {
      if ($element['#hash'] == $hash) {
        return $element;
      }
    }
    return NULL;
  }

  /**
   * Gets the value of an DOMNode.
   *
   * @param DOMNode $node
   * @return mixed
   *   The node's value if the node does not have any children. NULL otherwise.
   */
  public static function getNodeValue(DOMNode $node) {
    $contains_elements = $document->query('child::*', $node)->length > 0;
    $value = $contains_elements ? NULL : $node->nodeValue;
  }

  public static function DOMNodelistToArray(DOMNodeList $list) {
    $count = $list->length;
    $output = array();
    for ($i = 0; $i < $count; $i++) {
      $output[] = $list->item($i);
    }
    return $output;
  }

  public static function hasChildDOMElements(DOMNode $node) {
    $xpath = new DOMXPath($node->ownerDocument);
    $result = $xpath->query('child::*', $node);
    return $result->length > 0;
  }

}