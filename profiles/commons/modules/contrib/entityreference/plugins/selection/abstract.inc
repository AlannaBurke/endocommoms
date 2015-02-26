<?php

/**
 * @file
 * Abstraction of the selection logic of an entity reference field.
 *
 * Implementations that wish to provide an implementation of this should
 * register it using CTools' plugin system.
 */
interface EntityReference_SelectionHandler {
  /**
   * Factory function: create a new instance of this handler for a given field.
   *
   * @param $field
   *   A field datastructure.
   * @return EntityReferenceHandler
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL);

  /**
   * Return a list of referencable entities.
   *
   * @return
   *   An nested array of entities, the first level is keyed by the
   *   entity bundle, which contains an array of entity labels (safe HTML),
   *   keyed by the entity ID.
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0);

  /**
   * Count entities that are referencable by a given field.
   */
  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS');

  /**
   * Validate that entities can be referenced by this field.
   *
   * @return
   *   An array of entity ids that are valid.
   */
  public function validateReferencableEntities(array $ids);

  /**
   * Validate Input from autocomplete widget that has no Id.
   *
   * @see _entityreference_autocomplete_validate()
   *
   * @param $input
   * 	 Single string from autocomplete widget.
   * @param $element
   *   The form element to set a form error.
   * @return
   *   Value of a matching entity id, or NULL if none.
   */
  public function validateAutocompleteInput($input, &$element, &$form_state, $form);

  /**
   * Give the handler a chance to alter the SelectQuery generated by EntityFieldQuery.
   */
  public function entityFieldQueryAlter(SelectQueryInterface $query);

  /**
   * Return the label of a given entity.
   */
  public function getLabel($entity);

  /**
   * Generate a settings form for this handler.
   */
  public static function settingsForm($field, $instance);
}

/**
 * A null implementation of EntityReference_SelectionHandler.
 */
class EntityReference_SelectionHandler_Broken implements EntityReference_SelectionHandler {
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReference_SelectionHandler_Broken($field, $instance, $entity_type, $entity);
  }

  protected function __construct($field, $instance) {
    $this->field = $field;
    $this->instance = $instance;
  }

  public static function settingsForm($field, $instance) {
    $form['selection_handler'] = array(
      '#markup' => t('The selected selection handler is broken.'),
    );
    return $form;
  }

  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    return array();
  }

  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS') {
    return 0;
  }

  public function validateReferencableEntities(array $ids) {
    return array();
  }

  public function validateAutocompleteInput($input, &$element, &$form_state, $form) {
    return NULL;
  }

  public function entityFieldQueryAlter(SelectQueryInterface $query) {}

  public function getLabel($entity) {
    return '';
  }
}