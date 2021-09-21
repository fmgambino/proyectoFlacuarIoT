<div class="mdl-layout__drawer">
  <header>FLACUARIOT</header>
  <div class="scroll__wrapper" id="scroll__wrapper">
    <div class="scroller" id="scroller">
      <div class="scroll__container" id="scroll__container">
        <nav class="mdl-navigation">
          <a class="mdl-navigation__link <?php if (current_url() == base_url('main') ) {echo "mdl-navigation__link--current";} ?>" href="<?php echo base_url('main')?>">
            <i class="material-icons" role="presentation">dashboard</i>
            Dashboard
          </a>

          <a class="mdl-navigation__link <?php if (current_url() == base_url('devices') ) {echo "mdl-navigation__link--current";} ?>" href="<?php echo base_url('devices')?>">
            <i class="material-icons" role="presentation">devices</i>
            Dispositivos
          </a>

          

          <a class="mdl-navigation__link <?php if (current_url() == base_url('profile') ) {echo "mdl-navigation__link--current";} ?>" href="<?php echo base_url('profile')?>">
            <i class="material-icons" role="presentation">settings</i>
            Perfil
          </a>

          <div class="mdl-layout-spacer"></div>
          <hr>
          <a class="mdl-navigation__link" href="https://flacuariot.com">
            <i class="material-icons" role="presentation">link</i>
            flacuariot.com
          </a>
        </nav>
      </div>
    </div>
    <div class='scroller__bar' id="scroller__bar"></div>
  </div>
</div>
