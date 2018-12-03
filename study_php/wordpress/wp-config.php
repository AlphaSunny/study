<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'root');

/** MySQL database password */
define('DB_PASSWORD', '123456');

/** MySQL hostname */
define('DB_HOST', '127.0.0.1');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8mb4');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'pI]L*c`hE$Bd-Z?!9syo4QY;CfnbTRW|J/Kb&/$gtpp0Z8U#odrBYV-DjF;@ip*a');
define('SECURE_AUTH_KEY',  'e?z8Dm!rRd=QrJWviIO xjd=4JLNqWT6P}ZH,{X$pQo-A%U?$Vp$A:R4U=-9s~-X');
define('LOGGED_IN_KEY',    'ICE*^^3l:~~}T#*g2a :}@<ozlB1[tJouHE}=EC;2 [IDQ34c/ZtRg>.t6RvHukJ');
define('NONCE_KEY',        '?5xQGaR;}SO{V1W`S;}BtM=MO@WTp&A.BI~,LMw()-4vL;-xHrMR%L;qT(s2Dmpv');
define('AUTH_SALT',        '<Vzwk_6Pe4~FPW>pg&e@N>aVhE;>$`B{tL#eXE-z)`YdLBk<,MWVFmU!dRg+baf0');
define('SECURE_AUTH_SALT', 'vtSerUpC*-I.Zf7wVvX7&c4n}~^=Fq(=__$*Fh.GmHG]qm_2!F^soUYlaQL=U/E.');
define('LOGGED_IN_SALT',   'u_8U].)v@:}wk#;Q?ySwl~JG%sh</g/UaJ-_vBe]Bg5&]E0SC`S&ph;EvN)5E-~O');
define('NONCE_SALT',       '7$QaXpYZEH1+lT]GxkwquS{mZ ZVMfGlu_X_bD[!XOTyfvnb_J)h;8u2Qb<<gYT4');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
