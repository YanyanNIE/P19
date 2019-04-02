<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Accueil</title>
  <link rel="stylesheet" type="text/css" media="all"  href="/sr03/public/css/mystyle.css" />
</head>
<body>
  <header>
    <h1>TD SR03</h1>
  </header>
  <main>
    <article>
      <header>
        <h2>Vous n'êtes pas connecté !</h2>
      </header>

      <div class="login-page">
        <div class="form">
            <form method="GET" >
                <input type="hidden" name="action" value="authenticate">
                <input type="text" name="login" placeholder="login"/>
                <input type="password" name="mdp" placeholder="mot de passe"/>
                <button>login</button>
            </form>
        </div>
      </div>

      <?php
      if (isset($errmsg) && $errmsg == "nullvalue") {
        echo '<p class="errmsg">Saisissez le login et le mot de passe !</p>';
      }
      ?>
    </article>
  </main>
</body>
</html>
