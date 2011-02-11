<?php

function duplicates_edit_page()
{
  $checked_nides = variable_get('checked_nides', '');

  dpr($checked_nides);
  dpm($checked_nides);
}