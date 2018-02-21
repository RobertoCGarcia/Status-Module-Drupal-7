<?php

function form_status_module_email_config($form, &$form_state) {

     //Mensaje Inial.
     $message = '<p>' . t(' Configuración del Destinatario del Reporte ') . ' <p>';

     $form['description'] = array(
       '#type' => 'item',
       '#title' => $message,
     );

  return $form;

}