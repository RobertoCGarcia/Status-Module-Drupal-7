<?php

function form_status_module_config($form, &$form_state) {
   
     //$modulesStoreFormat = "Memcache#=#Varnish#=#Syslog#=#Database loggin#=#DFP#=#Comscore#=#Módule 1#=#Módule 2#=#Módulo 3#=#Módulo 4#=#Módulo 5#=#"; 
     //Construir la lista de modulos guardada
     $modulesStoreFormat = variable_get('form_status_formNameList');
     $tmpList = explode("#=#" , $modulesStoreFormat);
     $lst = "";
     $arrayLstModules = array();

     $arrayLstModules[] = "Selecciona un Módulo a Eliminar";
     foreach($tmpList as $clave => $valor){

   	    if( strlen($valor) != 0 ){
   	  	   $lst .=  ($clave + 1) . ".- ". $valor . "<br/>";
   	  	   $arrayLstModules[$valor] = $valor;  
   	    }
        
     }

     //Mensaje Inial.
     $message = '<p>' . t(' Escribe el nombre del Módulo que quieres revisar y presionar el botón salvar para incluirlo en la lista de Módulos a revisar') . ' <p>';

     //Lista Inial de Modulos Definidos.
     $listaInial = '<p>' . t( $lst ) . ' <p>';

     $form['description'] = array(
       '#type' => 'item',
       '#title' => t('Agregar un Módulo a la Lista'),
     );

     $form['module_name'] = array(
       '#type' => 'fieldset',
       '#title' => t('Datos del Módulo'),
       '#collapsible' => TRUE,
       '#collapsed' => FALSE,
     );

     $form['module_name']['introduction'] = array(
       '#markup' => $message,
     );

     $form['module_name']['nameModule'] = array(
       '#type' => 'textfield',
       '#title' => t('Nombre del Módulo'),
       '#description' => 'Nombre del Módulo a revisar',
       //'#size' => '30',
       //'#maxlength' => '30',
     );

    /*************************************************************/
    /* Lista de Módulos                                          */
    /*************************************************************/
    $form['description_lista'] = array(
      '#type' => 'item',
      '#title' => t('Módulo dentro de la Lista'),
    );

    $form['module_list'] = array(
      '#type' => 'fieldset',
      '#title' => t('Lista de Módulos'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['module_list']['introduction'] = array(
      '#markup' => $listaInial,
    );

    /*************************************************************/
    /* Eliminar Módulos                                          */
    /*************************************************************/
    //dpm($arrayLstModules);

    $delModulesMessage = '<p>' . t(' Selecciona de la lista el Módulo que se va a eliminar de la lista.') . '<p>';

    $form['eliminar_lista_modulos'] = array(
      '#type' => 'item',
      '#title' => t('Eliminar un Módulo de la Lista'),
    );

    $form['del_module_list'] = array(
      '#type' => 'fieldset',
      '#title' => t('Eliminar un Módulo'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['del_module_list']['message'] = array(
      '#markup' => $delModulesMessage,
    );

    # the values for the dropdown box
    $form['type_options'] = array(
      '#type' => 'value',
      '#value' => $arrayLstModules
    );

    $form['del_module_list']['typeModule'] = array(
      '#title' => t(' Selecciona el Módulo a Eliminar de la Lista'),
      '#type' => 'select',
      '#description' => "Selecciona el Módulo a Eliminar",
      '#options' => $form['type_options']['#value'],
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Actualizar Lista de Módulos'),
    );

  return $form;

}

function form_status_module_config_validate($form, $form_state) {

   /*	
   if(empty($form_state['values']['nameModule'])){
     form_set_error('nameModule','El Nombre del Módulo no puede estar en blanco');
   }
   */
     
   /** Validar para eliminar el módulo seleccionado*/
   //drupal_set_message( "typeModule: ". $form_state['values']['typeModule'] );   
 
}


function form_status_module_config_submit($form, $form_state) {
   
   //dpm($form_state);
   

   //Armar el almacenamiento del nuevo modulo a estar monitoreando

   //Validar que el nombre del módulo no este vacio, si esta vacio no se agrega
   if( strlen( $form_state['values']['nameModule'] ) != "0"){

        $formNameList = variable_get('form_status_formNameList');
        $newModule = $form_state['values']['nameModule']."#=#";
        $updatedformNameList = $formNameList.$newModule;
        variable_set('form_status_formNameList', $updatedformNameList);
        drupal_set_message("El Módulo ". $form_state['values']['nameModule'] ." ha sigo agregado de Forma correcta. ");
   }

   //Revisar si se va a eliminar algun módulo de la lista
   if( $form_state['values']['typeModule'] != "0"){

        $modulesStoreFormat = variable_get('form_status_formNameList');
        $tmpList = explode("#=#" , $modulesStoreFormat);

        foreach($tmpList as $clave => $valor){

   	       if( strlen($valor) != 0 ){

   	       	    //Validar que el módulo sea el correcto para eliminarlo de la lista principal
   	  	        if( $valor == $form_state['values']['typeModule']){
         	        //drupal_set_message(" valor: ". $valor ."  form_stat[values][typeModule]: " . $form_state['values']['typeModule'] );
   	  	        }else{
   	  	        	$moduleListUpdated.= $valor."#=#";
   	  	        }

   	  	        variable_set('form_status_formNameList', $moduleListUpdated);
   	            

   	       }
        
        }

        drupal_set_message("El Módulo ". $form_state['values']['typeModule'] ." ha sigo eliminado de Forma correcta."); 
       
   }


}