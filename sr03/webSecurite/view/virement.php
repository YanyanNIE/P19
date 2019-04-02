<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Virement</title>
  <link rel="stylesheet" type="text/css" media="all"  href="/sr03/public/css/mystyle.css" />
</head>
<body>
  <header>
    <h1>Virement</h1>
  </header>
  <main>
    <article>
      <header>
        <h2>Bienvenue <?php echo $_SESSION["connected_user"]["prenom"];?> <?php echo $_SESSION["connected_user"]["nom"];?></h2>
      </header>
<?php if (isset($virement_ok)) { ?>
  <h4>Virement effectué avec succès !</h4>
<?php } else { ?>
  <div class="form">
    <form method="GET" >
      <input type="hidden" name="action" value="dovirement">
      <input type="text" name="emetteur" readonly="true" value="<?php echo $_GET["numero_compte"];?>">
      <select name="beneficiaire">
        <option value="">Choix bénéficiaire</option>
        <?php
        foreach ($listeUsers as $cle => $unUser) {
          echo '<option value="'.$unUser['numero_compte'].'">'.$unUser['numero_compte'].' - '.$unUser['nom'].' '.$unUser['prenom'].'</option>';
        }
        ?>
      </select>
      <input name="montant" type="text" placeholder="montant" />
      <button>Effectuer le virement</button>
    </form>
  </div>
<?php } ?>

      <div class="form">
        <form method="GET" >
          <input type="hidden" name="action" value="home">
          <button>Accueil</button>
        </form>
      </div>
    </article>
  </main>
</body>
</html>
