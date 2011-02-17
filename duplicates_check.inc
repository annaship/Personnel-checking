<?php

//TODO: sort by last name
//TODO: clear theme cashe


function duplicates_check_page()
{
  drupal_rebuild_theme_registry();
  return drupal_get_form('duplicates_check_form');
}


function duplicates_check_form($form_state) {
  $form = array();
  $nids = _get_nids();

  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'duplicates_check_form_table',
  );

  foreach($nids as $nid) {
    $form['container']['node_' . $nid] = array(
      '#type' => 'checkbox',
      '#title' => NULL,
      '#size' => 4,
      '#default_value' => 0,
    );
  }

//  $form['#redirect'] = 'duplicates_edit';

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}

function duplicates_check_form_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    $e = preg_match("/node_(\d+)/", $key, $matches);
    $nid = $matches[1];
    if (preg_match("/node/", $key) AND $value == 1) {
      $checked[] = $nid;
    }
  }
  variable_set('checked_nides', $checked);
  $current_destination = drupal_get_destination();
  if (count($checked) != 2) {
    drupal_set_message('Please check two nodes');
  }
  else {
    drupal_goto('duplicates_edit', $current_destination);
  }
}

function duplicates_check_theme($existing, $type, $theme, $path) {
  return array(
    'duplicates_check_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}


function theme_duplicates_check_form_table($container) {
//  dpm($container);
//  if (empty($container['value'])) {
//    drupal_set_message("There are no duplicates");
//  }
//  else {
  $nids = array();
  foreach($container as $field_name => $field) {
    // All the fields were named 'node_' . $node->nid
    if (strpos($field_name, 'node_') === 0) {

      $nid = substr($field_name, 5);
      $nids[] = array($nid => $field);
    }
  }

  if (empty($nids)) {
    drupal_set_message("There are no duplicates");
  }
  elseif (!empty($nids)) {
    $header = array(t('Nid'), t('First Name'), t('Last Name'), t('Email'), t('Compare'));
    $rows = array();

    foreach ($nids as $value) {
      foreach($value as $nid => $field) {
        // All the fields were named 'node_' . $node->nid
          $node = node_load($nid);

          $rows[] = array(
            $node->nid,
            check_plain($node->field_person_first_name[0]['value']),
            check_plain($node->field_person_last_name[0]['value']),
            check_plain($node->field_person_email[0]['email']),
            drupal_render($field),
          );
      }
    }
    return theme_table($header, $rows);
  }
}

function _get_nids() {
  $nids = array();
  $sql = "SELECT nid from {content_type_person} WHERE field_person_last_name_value in (
              SELECT field_person_last_name_value
              FROM {content_type_person}
              GROUP BY field_person_last_name_value
              HAVING (COUNT(field_person_last_name_value) > 1)
            ORDER BY field_person_last_name_value
          );";

  $db_result = db_query($sql);
  while ($nid = db_result($db_result)) {
    $nids[] = $nid;
  }
  return $nids;
}