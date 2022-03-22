<header class="mdl-layout__header">
    <div class="mdl-layout__header-row">
        <div class="mdl-layout-spacer"></div>
        <!-- Search-->
        <select id="device_select" onchange="change_device()" class="" name="" style="background:transparent;color:#d1d0cf">
          <option value="">Select Device</option>
          <?php foreach ($devices as $device ) { ?>
            <option value="<?php echo $device['device_id'] ?>" <?php if ($_SESSION['selected_device'] == $device['device_id']){echo "selected";} ?>><?php echo $device['device_alias']?></option>
          <?php } ?>
        </select>



        <div class="avatar-dropdown" id="icon">
            <span><?php echo $_SESSION['user_name']; ?></span>
            <img src="<?php echo $_SESSION['user_image']; ?>">
        </div>
        <!--
        <ul class="mdl-menu mdl-list mdl-menu--bottom-right mdl-js-menu mdl-js-ripple-effect mdl-shadow--2dp account-dropdown"
            for="icon">
            <li class="mdl-list__item mdl-list__item--two-line">
                <span class="mdl-list__item-primary-content">
                    <span class="material-icons mdl-list__item-avatar"></span>
                    <span>Luke</span>
                    <span class="mdl-list__item-sub-title">Luke@skywalker.com</span>
                </span>
            </li>
            <li class="list__item--border-top"></li>
            <li class="mdl-menu__item mdl-list__item">
                <span class="mdl-list__item-primary-content">
                    <i class="material-icons mdl-list__item-icon">account_circle</i>
                    My account
                </span>
            </li>
            <li class="mdl-menu__item mdl-list__item">
                <span class="mdl-list__item-primary-content">
                    <i class="material-icons mdl-list__item-icon">check_box</i>
                    My tasks
                </span>
                <span class="mdl-list__item-secondary-content">
                  <span class="label background-color--primary">3 new</span>
                </span>
            </li>
            <li class="mdl-menu__item mdl-list__item">
                <span class="mdl-list__item-primary-content">
                    <i class="material-icons mdl-list__item-icon">perm_contact_calendar</i>
                    My events
                </span>
            </li>
            <li class="list__item--border-top"></li>
            <li class="mdl-menu__item mdl-list__item">
                <span class="mdl-list__item-primary-content">
                    <i class="material-icons mdl-list__item-icon">settings</i>
                    Settings
                </span>
            </li>
            <a href="login.html">
                <li class="mdl-menu__item mdl-list__item">
                    <span class="mdl-list__item-primary-content">
                        <i class="material-icons mdl-list__item-icon text-color--secondary">exit_to_app</i>
                        Log out
                    </span>
                </li>
            </a>
        </ul>
        Account dropdawn-->
        <button id="more"
                class="mdl-button mdl-js-button mdl-button--icon">
            <i class="material-icons">more_vert</i>
        </button>

        <ul class="mdl-menu mdl-menu--bottom-right mdl-js-menu mdl-js-ripple-effect mdl-shadow--2dp settings-dropdown"
            for="more">
            <a class="mdl-menu__item" href="https://flacuariot.com/app/devices">
                Configuración
            </a>
            <a class="mdl-menu__item" href="https://flacuariot.com/soporte/">
                Soporte
            </a>
            <a class="mdl-menu__item" href="https://flacuariot.com/faq">
                F.A.Q.
            </a>
            <a href="logout">
                <li class="mdl-menu__item mdl-list__item">
                    <span class="mdl-list__item-primary-content">
                        <i class="material-icons mdl-list__item-icon text-color--secondary">exit_to_app</i>
                        Salir
                    </span>
                </li>
            </a>
    </div>
</header>

<script type="text/javascript">
  function change_device(){

    var device_id = $("#device_select").val();
    console.log(device_id);
    $.post("<?php echo base_url('devices/change_device'); ?>", {device_id: device_id}, function(result){
      location.reload();
    });
  }
</script>
