const express = require('express');
const morgan = require('morgan');
const helmet = require('helmet');
const { exec } = require('child_process');
const path = require('path');
const util = require('util');
const execAsync = util.promisify(exec);

const app = express();
const port = 3000;
const mainPath = path.join(__dirname, '../main');

app.use(helmet());
app.use(express.json());
app.use(morgan('combined'));

app.use((req, res, next) => {
  const pocetak = process.hrtime();
  res.on('finish', () => {
    const [sec, nano] = process.hrtime(pocetak);
    const ms = sec * 1e3 + nano / 1e6;
    console.log(`${req.method} ${req.originalUrl} - ${ms.toFixed(3)} ms`);
  });
  next();
});

app.get('/status', (req, res) =>
  res.json({ status: 'OK', vrijeme: new Date().toISOString() })
);

async function runCommand(naredba) {
  const { stdout, stderr } = await execAsync(naredba);
  if (stderr) console.error('[C++]', stderr);
  return stdout.trim();
}

app.post('/data', async (req, res, next) => {
  try {
    const { key, value } = req.body;
    if (!key || !value)
      return res.status(400).json({ greska: 'Nedostaje ključ ili vrijednost' });

    const rezultat = await runCommand(`${mainPath} insert ${key} ${value}`);
    res.json({ rezultat });
  } catch (err) {
    next(err);
  }
});

app.get('/data/:key', async (req, res, next) => {
  try {
    const key = req.params.key;
    if (!key)
      return res.status(400).json({ greska: 'Nedostaje ključ' });

    const rezultat = await runCommand(`${mainPath} get ${key}`);
    res.json({ rezultat });
  } catch (err) {
    next(err);
  }
});

app.put('/data/:key', async (req, res, next) => {
  try {
    const key = req.params.key;
    const { value } = req.body;
    if (!value)
      return res.status(400).json({ greska: 'Nedostaje vrijednost' });

    const rezultat = await runCommand(`${mainPath} update ${key} ${value}`);
    res.json({ rezultat });
  } catch (err) {
    next(err);
  }
});

app.delete('/data/:key', async (req, res, next) => {
  try {
    const key = req.params.key;
    const rezultat = await runCommand(`${mainPath} delete ${key}`);
    res.json({ rezultat });
  } catch (err) {
    next(err);
  }
});

app.use((err, req, res, next) =>
  res.status(500).json({ greska: 'Interna pogreška poslužitelja' })
);

app.listen(port, () =>
  console.log(`Slušam na http://localhost:${port}`)
);
