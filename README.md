<p>Some sources
	<ul>in english : https://datatracker.ietf.org/doc/html/rfc2812#section-1</ul>
	<ul>in french : http://abcdrfc.free.fr/rfc-vf/rfc1459.html</ul>
</p>
<p>Mon travail
<ul> mon so.notion avec un debrousaillage (j'ai besoin de vos mail pour vous inviter) https://www.notion.so/RFC-1459-Franc-ais-3d787c459ef14c849fa3ece854073952</ul>
</p>
<p> Les tâches que j'ai relevé pour le moment :
<ul>gerer l'authentification par nickname et username</ul>
<ul>gerer la creation/destruction de canaux</ul>
<ul>gerer 3 types d'utilisateur : basiques, operateur de canal, operateur irc (pencez a voir les points 8.12.2 et 8.12.4 de la doc)</ul>
<ul>gestions de differents types de messages, ie, envoyé :
    <li>a une liste</li>
    <li>a un canal</li>
    <li>a tout utilisateur du serveur (meme genre de methode que pour a un canal)</li>
</ul>
<ul>creer differentes cmds :
    <li>etablissement de connexion : PASS / NICK / USER / OPER / QUIT</li>
    <li>operations sur un canal : JOIN / PART / MODE (pour mode, il y a plein d'options) / TOPiC / NAMES / LIST / INVITE / KICK</li>
    <li>Requetes et cmd serveur : VERSION / STATS / TIME / iNVITE / ADMIN (penser a voir 8.12.4 de la doc) / INFO</li>
    <li>envoi de messages : PRIVMSG / NOTICE</li>
    <li>Requete basee sur les utilisateurs : WHO / WHOIS / WHOWAS</li>
    <li>messages divers : KiLL / PING / PONG / ERROR </li>
    <li>messages optionnels : AWAY / REHASH / RESTART / SUMMON (? la je suis pas sure) / USERS / WALLOPS / USERHOST / ISON</li>
</ul>
<ul>faire LE ficher de configuration</ul>
<ul>lister les reponses numeriques </ul>
</p>