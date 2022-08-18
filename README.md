<p>Some sources
	<ul>in english : https://datatracker.ietf.org/doc/html/rfc2812</ul>
	<ul>in french : http://abcdrfc.free.fr/rfc-vf/rfc1459.html</ul>
	<ul> https://modern.ircdocs.horse/</ul>
	<ul>http://www.codingbison.com/c/c-sockets-introduction.html</ul>
	<ul>petit split par ' ' : https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/</ul>
	<ul>https://www.unrealircd.org/docs/User_modes</ul>
	<ul>Identification Protocol : https://www.rfc-editor.org/rfc/rfc1413</ul>
</p>
<p><!-- Mon travail-->
<!-- <ul> mon so.notion avec un debrousaillage (j'ai besoin de vos mail pour vous inviter) https://www.notion.so/RFC-1459-Franc-ais-3d787c459ef14c849fa3ece854073952</ul> -->
<ul> Les tâches que j'ai relevé pour le moment :
	<li>gerer l'authentification par nickname et username</li>
	<li>gerer la creation/destruction de canaux</li>
	<li>gerer 3 types d'utilisateur : basiques, operateur de canal, operateur irc <!-- (pensez a voir les points 8.12.2 et 8.12.4 de la doc) --></li>
	<li>gestions de differents types de messages, ie, envoyé :
		<ul>
			<li>a une liste</li>
			<li>a un canal</li>
			<li>a tout utilisateur du serveur (meme genre de methode que pour a un canal)</li>
		</ul>
	</li>
	<li>creer differentes cmds :
		<ul>
			<li>etablissement de connexion :
				<strike>PASS</strike> / 
				<strike>NICK</strike> / 
				<strike>USER</strike> / 
				<strike>OPER</strike> / 
				<strike>QUIT</strike>
			</li>
			<li>operations sur un canal (a check avant de se lancer) : 
				<strike>JOIN</strike> / 
				<strike>PART</strike> / 
				<strike>MODE (il y a plein d'options et toutes ne sont pas a faire)</strike> / 
				<strike>TOPIC</strike> / 
				<strike>NAMES</strike> / 
				<strike>LIST</strike> / 
				<strike>INVITE</strike> / 
				<strike>KICK</strike>
			</li>
			<!-- <li>Requetes et cmd serveur : VERSION / STATS / TIME / iNVITE / ADMIN (penser a voir 8.12.4 de la doc) / INFO</li> -->
			<li>envoi de messages : 
				<strike>PRIVMSG</strike> /
				<strike>NOTICE</strike>
			</li>
			<!-- <li>Requete basee sur les utilisateurs : WHO / WHOIS / WHOWAS</li> -->
			<li>messages divers : 
				KILL / 
				<strike>PING</strike> / 
				<strike>PONG</strike> / 
				<strike>ERROR</strike>
			</li>
			<!-- <li>messages optionnels : AWAY / REHASH / RESTART / SUMMON (? la je suis pas sure) / USERS / WALLOPS / USERHOST / ISON</li> -->
		</ul>
	</li>
	<li><strike>faire LE ficher de configuration</strike></li>
	<li><strike>lister les reponses numeriques</strike></li>
</ul>
</p>