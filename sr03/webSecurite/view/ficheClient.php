<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Clients</title>
  <link rel="stylesheet" type="text/css" media="all"  href="/sr03/public/css/mystyle.css" />
</head>
<body>
  <header>
    <h1>Liste clients</h1>
  </header>
  <main>
    <article>
      <header>
        <h2>Bienvenue <?php echo $_SESSION["connected_user"]["prenom"];?> <?php echo $_SESSION["connected_user"]["nom"];?></h2>
      </header>
      <div class="liste">
          <table>
            <?php
            foreach ($listeUsers as $cle => $unUser) {
              echo '<tr>';
              echo '<td>'.$unUser['nom'].'</td>';
              echo '<td>'.$unUser['prenom'].'</td>';
              echo '<td><a href="?action=virement&numero_compte='.$unUser['numero_compte'].'">'.$unUser['numero_compte'].'</a></td>';
              echo '</tr>';
            }

             ?>
          </table>
      </div>
      <div class="form">
        <form method="GET">
          <input type="hidden" name="action" value="home">
          <button>Accueil</button>
        </form>
      </div>
    </article>
  </main>
</body>
</html>
