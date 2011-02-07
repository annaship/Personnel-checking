<?php

//require_once('two_person_form_submit.inc');

function two_person_form($form_state) {
  $form = array();
//  unset($last_settings);
//  $new_person_nid  = variable_get('new_person_nid', '');
////  $new_person_node = _get_new_person_node($new_person_nid);
//  $old_person_nids = variable_get('old_person_nids', '');
//  $new_last_name   = $new_person_node['last_name'];
////  $old_person_nids = ($new_last_name);
//
////  $nodes = $new_person_node;
////  $nodes += _two_person_items($old_person_nids);
//
//  $new_a = array();
//  $new_a[] = node_load($new_person_nid);
//  $old_a = _two_person_items($old_person_nids);
//
//  $nodes = array_merge($new_a, $old_a);
//
////  $nodes = _two_person_items($old_person_nids);
//  $form['#redirect'] = 'two_person';
  $checked_nids  = variable_get('person_checked', '');

  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'two_person_form_table',
  );

  foreach($checked_nids as $nid) {
    $form['container']['node_' . $nid] = array(
      '#type' => 'checkbox',
      '#title' => NULL,
      '#size' => 4,
      '#default_value' => 0,
    );
  }

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}

//function two_person_form_validate($form, &$form_state) {
//  foreach($form_state['values'] as $field_name => $value) {
//    if(strpos($field_name, 'node_') === 0) {
//      if(!is_numeric($value) || intval($value) < 0) {
//        form_set_error($field_name, t('Value must be a non-negative integer.'));
//      }
//    }
//  }
//}

function two_person_form_submit($form, &$form_state) {
  drupal_set_message('two_person_form_submit');
//  drupal_set_message(t('The form has been submitted.'));
//  $checked = array();
//
////$a = $form_state['values'];
//foreach ($form_state['values'] as $key => $value) {
//  $e = preg_match("/node_(\d+)/", $key, $matches);
//  $nid = $matches[1];
//  if (preg_match("/node/", $key) AND $value == 1) {
//    $checked[] = $nid;
//  }
//}
////    dpm($checked);
//
//  $current_destination = drupal_get_destination();
//  if (checked_validation($checked)) {
//    variable_set('person_checked', $checked);
//    dpm($checked);
////    drupal_goto('two_person_compare', $current_destination);
//
//  } else {
//    drupal_goto('two_person', $current_destination);
//  }

}

//function checked_validation($checked) {
////  TODO: what to do if 0? all are different?
//  if (count($checked) != 2) {
//    drupal_set_message('Please select two values.');
//// TODO:   goes to csv2drupal!!!, should to 'two_person'
//    return 0;
////    drupal_goto('two_person', $current_destination);
//  } else {
////    drupal_goto('two_person_compare', $current_destination);
//    return 1;
//  }
//}

function two_person_theme($existing, $type, $theme, $path) {
  drupal_set_message('two_person_theme');
  return array(
    'two_person_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}


function theme_two_person_form_table($container) {
  drupal_set_message('theme_two_person_form_table');
  // Define header row for the table
  $header = array(t('Nid'), t('First Name'), t('Last Name'));

  $rows = array();
  $rows = array('a', 'b', 'c');

//  foreach($container as $field_name => $field) {
//
//    // All the fields were named 'node_' . $node->nid
//    if (strpos($field_name, 'node_') === 0) {
//
//      $nid = substr($field_name, 5);
//      $node = node_load($nid);
//
//      $rows[] = array(
//        $node->nid,
//        check_plain($node->field_person_first_name[0]['value']),
//        check_plain($node->field_person_last_name[0]['value']),
//        check_plain($node->field_person_email[0]['email']),
//        drupal_render($field),
//      );
//
//    }
//  }

  return theme_table($header, $rows);
}

//function two_person_form_submit($form, &$form_state) {
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


function _two_person_items($old_person_nids) {
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


//
//function two_person_form() {
////  dpr('Utro!');
//  $checked_nids  = variable_get('person_checked', '');
//
//  $form = array();
//  $form['container'] = array(
//    '#type' => 'markup',
//    '#value' => '',
//    '#theme' => 'two_person_form_table',
//  );
//
//  foreach($checked_nids as $nid) {
//    $form['container']['node_' . $nid] = array(
//      '#type' => 'checkbox',
//      '#title' => NULL,
//      '#size' => 4,
//      '#default_value' => 0,
//    );
//  }
//
//  $form['submit'] = array (
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//    );
//
//  return $form;
//}
//
//function two_person_form_submit($form, &$form_state) {
//  drupal_set_message('two_person_form_submit');
//}
//
//
//function two_person_form_theme($existing, $type, $theme, $path) {
//  return array(
//    'two_person_form_table' => array(
//      'arguments' => array('fieldset' => NULL),
//    )
//  );
//}
//
//
//function theme_two_person_form_table($container) {
//  drupal_set_message('theme_two_person_form_table');
//
////  $transformed_container = _regroup_two_person_data($checked_nids);
////  if(!empty($transformed_container)) {
////    $header = array(
//////      '',
////      'data' => '',
////      array('data' => t('First Person'), 'field' => 'first_person'),
////      array('data' => t('Second Person'), 'field' => 'second_person'),
////    );
////  }
//  $header = array(t('Nid'), t('First Name'), t('Last Name'));
//  $rows[] = array('a', "b", "c");
//
////  $header = array(t('Nid'), t('First Name'), t('Last Name'), t('Email'), t('Compare'));
////
////  $rows = array();
////
////  foreach($container as $field_name => $field) {
////
////    // All the fields were named 'node_' . $node->nid
////    if (strpos($field_name, 'node_') === 0) {
////
////      $nid = substr($field_name, 5);
////      $node = node_load($nid);
////
////      $rows[] = array(
////        $node->nid,
////        check_plain($node->field_person_first_name[0]['value']),
////        check_plain($node->field_person_last_name[0]['value']),
////        check_plain($node->field_person_email[0]['email']),
////        drupal_render($field),
////      );
////
////    }
////  }
////
//  return theme_table($header, $rows);
//}
//
//
//
//function my_display_function() {
//  //db query
//  $sql = "SELECT * from users WHERE users.uid > 0";
//
//  //set limit for pager
//  $limit = 25;
//  //define table header
//  $header = array(
//    '', //note empty value, will use this later
//    array('data' => t('User ID'), 'field' => 'uid', 'sort' => 'asc'),
//    array('data' => t('Username'), 'field' => 'name'),
//    array('data' => t('Status'), 'field' => 'status'),
//  );
//  //alows sorting
//  $tablesort = tablesort_sql($header);
//  //adds a pager to results - show 25 per page
//  $result = pager_query($sql.$tablesort, $limit);
//  $form = array();
//  while($item = db_fetch_object($result)) {
//
//    /*Add each user id to my checkboxes array.
//    Only keys, no values */
//    $checkboxes[$item->uid] = '';
//
//    // You need unique keys for each user, so I use user id
//    $form['uid'][$item->uid] = array(
//      '#value' => $item->uid
//    );
//    $form['name'][$item->uid] = array(
//      '#value' => l($item->name, 'user/'.$item->uid)
//    );
//   //
//   $form['status'][$item->uid] = array(
//      '#value' => $item->status
//    );
//
//  }
//
//  $form['checkboxes'] = array('#type' => 'checkboxes', '#options' => $checkboxes);
//  $form['pager'] = array('#value' => theme('pager', NULL, $limit, 0));
//
//  return $form;
//
//}
//
//function _regroup_two_person_data($checked_nids) {
//  $comparison = array();
//  if(!empty($checked_nids)) {
//    foreach ($checked_nids as $checked_nid) {
//      $node                         = node_load($checked_nid);
//      $comparison['first_name'][]  	= $node->field_person_first_name[0]['value'];
//      $comparison['last_name'][]  	= $node->field_person_last_name[0]['value'];
//      $comparison['organization'][] = $node->field_person_organization[0]['value'];
//      $comparison['title'][]  			= $node->field_person_title[0]['value'];
//      $comparison['address'][]  		= $node->field_person_address[0]['value'];
//      $comparison['city'][]         = $node->field_person_city[0]['value'];
//      $comparison['state'][]  			= $node->field_person_state[0]['value'];
//      $comparison['zipcode'][]  		= $node->field_person_zipcode[0]['value'];
//      $comparison['country'][]  		= $node->field_person_country[0]['value'];
//      $comparison['phone'][]  			= $node->field_person_phone[0]['value'];
//      $comparison['fax'][]          = $node->field_person_fax[0]['value'];
//      $comparison['email'][]  			= $node->field_person_email[0]['email'];
//      $comparison['personid'][]  		= $node->field_person_personid[0]['value'];
//      $comparison['role'][]         = $node->field_person_role[0]['value'];
//      $comparison['uid'][]          = $node->field_person_uid[0]['uid'];
//    }
//  }
//  return($comparison);
//}
