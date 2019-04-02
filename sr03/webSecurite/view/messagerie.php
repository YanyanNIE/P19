<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Messages</title>
  <link rel="stylesheet" type="text/css" media="all"  href="/sr03/public/css/mystyle.css" />
</head>
<body>
  <header>
    <h1>Messages</h1>
  </header>
  <main>
    <article>
      <header>
        <h2>Bienvenue <?php echo $_SESSION["connected_user"]["prenom"];?> <?php echo $_SESSION["connected_user"]["nom"];?></h2>
      </header>

      <div class="liste">
        <h3>Messages reçus</h3>
        <table>
          <?php
          foreach ($messagesRecus as $cle => $message) {
            echo '<tr>';
            echo '<td>'.$message['nom'].' '.$message['prenom'].'</td>';
            echo '<td>'.$message['sujet_msg'].'</td>';
            echo '<td>'.$message['corps_msg'].'</td>';
            echo '</tr>';
          }
           ?>
        </table>
      </div>

      <div class="liste">
        <h3>Messages envoyés</h3>
        <table>
          <?php
          foreach ($messagesEnvoyes as $cle => $message) {
            echo '<tr>';
            echo '<td>'.$message['nom'].' '.$message['prenom'].'</td>';
            echo '<td>'.$message['sujet_msg'].'</td>';
            echo '<td>'.$message['corps_msg'].'</td>';
            echo '</tr>';
          }
           ?>
        </table>
      </div>

      <div class="form">
        <form method="GET" >
          <input type="hidden" name="action" value="sendmsg">
          <select name="destinataire">
            <option value="">Choix destinataire</option>
            <?php
            foreach ($listeUsers as $cle => $unUser) {
              echo '<option value="'.$unUser['login_user'].'">'.$unUser['nom'].' '.$unUser['prenom'].'</option>';
            }
            ?>
          </select>
          <input name="sujet" type="text" placeholder="sujet" />
          <textarea name="corps" rows="3" cols="40"></textarea>
          <button>Envoyer le message</button>
        </form>
      </div>

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
