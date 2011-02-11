<?php

//TODO: change references in all CCT

function duplicates_check_form($form_state) {
  $form = array();
  unset($last_settings);

  $nids = array(47,
            48,
            37806,
            37883);

//  $nodes = _duplicates_check_items($old_person_nids);
//  $form['#redirect'] = 'two_person';

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

//TODO: only 2 boxes should be checked!
function duplicates_check_form_submit($form, &$form_state) {
//  dpm('Submit!!!');
  foreach ($form_state['values'] as $key => $value) {
  $e = preg_match("/node_(\d+)/", $key, $matches);
  $nid = $matches[1];
  if (preg_match("/node/", $key) AND $value == 1) {
    $checked[] = $nid;
  }
}
  dpm($checked);
  variable_set('checked_nides', $checked);
  $current_destination = drupal_get_destination();
  dpm('$checked.size = ' . count($checked));
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

  // Define header row for the table
  $header = array(t('Nid'), t('First Name'), t('Last Name'), t('Email'), t('Compare'));

  $rows = array();

  foreach($container as $field_name => $field) {

    // All the fields were named 'node_' . $node->nid
    if (strpos($field_name, 'node_') === 0) {

      $nid = substr($field_name, 5);
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

