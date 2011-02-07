<?php

//require_once('personell_check_form_submit.inc');

function personell_check_form($form_state) {
  $form = array();
  unset($last_settings);
  $new_person_nid  = variable_get('new_person_nid', '');
//  $new_person_node = _get_new_person_node($new_person_nid);
  $old_person_nids = variable_get('old_person_nids', '');
  $new_last_name   = $new_person_node['last_name'];
//  $old_person_nids = ($new_last_name);

//  $nodes = $new_person_node;
//  $nodes += _personell_check_items($old_person_nids);

  $new_a = array();
  $new_a[] = node_load($new_person_nid);
  $old_a = _personell_check_items($old_person_nids);

  $nodes = array_merge($new_a, $old_a);

//  $nodes = _personell_check_items($old_person_nids);
  $form['#redirect'] = 'two_person';
  
  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'personell_check_form_table',
  );

  foreach($nodes as $node) {
    $form['container']['node_' . $node->nid] = array(
      '#type' => 'checkbox',
      '#title' => NULL,
      '#size' => 4,
      '#default_value' => 0,
    );
  }

//  $form['new_person'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('New personnel data'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//
//  $form['new_person']['first_name'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('First name'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['first_name'],
//    // '#description' => t('Site name acronym'),
//  );
//
//    $form['new_person']['last_name'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Last name'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['last_name'],
//    // '#description' => t('Site name acronym'),
//  );
//
//    $form['new_person']['email'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Email'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['email'],
//    // '#description' => t('Site name acronym'),
//  );
//
//
//  $form['old_persons'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Existing personnel data'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form['old_persons']['first_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('first_name'),
//    '#default_value' => t('first_name'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//  $form['old_persons']['last_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('last_name'),
//    '#default_value' => t('last_name'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//  $form['old_persons']['email'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('email'),
//    '#default_value' => t('email'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}

//function personell_check_form_validate($form, &$form_state) {
//  foreach($form_state['values'] as $field_name => $value) {
//    if(strpos($field_name, 'node_') === 0) {
//      if(!is_numeric($value) || intval($value) < 0) {
//        form_set_error($field_name, t('Value must be a non-negative integer.'));
//      }
//    }
//  }
//}

function personell_check_form_submit($form, &$form_state) {
  drupal_set_message(t('The form has been submitted.'));
  $checked = array();

//$a = $form_state['values'];
foreach ($form_state['values'] as $key => $value) {
  $e = preg_match("/node_(\d+)/", $key, $matches);
  $nid = $matches[1];
  if (preg_match("/node/", $key) AND $value == 1) {
    $checked[] = $nid;
  }
}
//    dpm($checked);

  $current_destination = drupal_get_destination();
  if (checked_validation($checked)) {
    variable_set('person_checked', $checked);
    dpm($checked);
//    drupal_goto('two_person_compare', $current_destination);

  } else {
    drupal_goto('personell_check', $current_destination);
  }

}

function checked_validation($checked) {
//  TODO: what to do if 0? all are different?
  if (count($checked) != 2) {
    drupal_set_message('Please select two values.');
// TODO:   goes to csv2drupal!!!, should to 'personell_check'
    return 0;
//    drupal_goto('personell_check', $current_destination);
  } else {
//    drupal_goto('two_person_compare', $current_destination);
    return 1;
  }
}

function personell_check_theme($existing, $type, $theme, $path) {
  return array(
    'personell_check_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}


function theme_personell_check_form_table($container) {

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

//function personell_check_form_submit($form, &$form_state) {
//  drupal_set_message(t('The form has been submitted.'));
//}

//function two_person_page() {
////  $sql = "SELECT nid FROM {node} WHERE created >= %d ORDER BY nid DESC";
//  dpr('HERE2!');
//  dpm('UUU2');
//  print('Blah2!');
//}


//function my_module_theme() {
//    return array(
//      'my_theme_function' => array(
//      'arguments' => array(),
//    ));
//}



function _get_new_person_node($new_person_nid) {
  $new_person = array();
  $node       = node_load($new_person_nid);
  $new_person['first_name'] = $node->field_person_first_name[0]['value'];
  $new_person['last_name']  = $node->field_person_last_name[0]['value'];
  $new_person['email']      = $node->field_person_email[0]['email'];

  return $new_person;
}


function _personell_check_items($old_person_nids) {
  $res = array();
  if ($old_person_nids) {
    foreach ($old_person_nids as $value) {
      $res[] = node_load($value);
    }
  }

  if (count($res) == 0) {
    drupal_set_message(t("Couldn't find any nodes!"), 'warning');
  }
  return $res;
}

