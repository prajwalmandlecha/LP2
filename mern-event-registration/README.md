# 🎟️ Global Event Registration System

An event management and registration portal for high-traffic cloud environments. This system demonstrates robust data handling and modern UI/UX design.

## 🚀 Key Features

- **Dynamic Registration:** Responsive React forms for efficient event data capture.
- **Backend Validation:** Express-level schema validation for data integrity.
- **Self-Contained DB:** Utilizes a local MongoDB instance for rapid read/write operations.
- **Manual Deployment:** Fully optimized for terminal-based setup on Azure/AWS VMs.

## 🛠️ Technology Stack

- **Frontend:** React, Axios, Eventful Theme
- **Backend:** Node.js, Express, Mongoose
- **Database:** MongoDB (Local Community Server)
- **Execution:** PM2 Process Management

## ☁️ Ubuntu VM Deployment on Azure/AWS

Use these steps when deploying the project on an Ubuntu virtual machine.

### 1. Create the Ubuntu VM

1. Create an Ubuntu Server VM on Azure or an AWS EC2 Ubuntu instance.
2. Choose a small instance size for testing, for example 1 vCPU and 1-2 GB RAM.
3. Download or create the SSH key during VM creation.
4. During VM creation, allow inbound traffic on:
   - `22` for SSH
   - `80` for HTTP
   - `443` for HTTPS
5. After the VM is created, add one more inbound security rule for the backend API:
   - Type: Custom TCP
   - Port: `5000`
   - Source: Any
6. Connect to the VM:
   ```bash
   ssh -i yourkey.pem azureuser@YOUR_PUBLIC_IP
   ```

### 2. Update Ubuntu and Install Nginx

```bash
sudo apt update
sudo apt-get install -y nginx
sudo systemctl status nginx
```

Make sure Nginx shows `active (running)`.

### 3. Install MongoDB

If you are on Ubuntu 24.04 (noble), install MongoDB 8.0 with the official repository and keyring:

```bash
sudo apt-get update
sudo apt-get install -y gnupg curl
curl -fsSL https://www.mongodb.org/static/pgp/server-8.0.asc | sudo gpg -o /usr/share/keyrings/mongodb-server-8.0.gpg --dearmor
echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-8.0.gpg ] https://repo.mongodb.org/apt/ubuntu noble/mongodb-org/8.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-8.0.list
sudo apt-get update
sudo apt-get install -y mongodb-org
sudo systemctl daemon-reload
sudo systemctl start mongod
sudo systemctl status mongod
```

Make sure MongoDB shows `active (running)`.

### 4. Install Node.js

Install `nvm` and Node.js 24 before running the backend or frontend:

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.4/install.sh | bash
. "$HOME/.nvm/nvm.sh"
nvm install 24
node -v
npm -v
```

### 5. Clone the Repository

```bash
git clone https://github.com/prajwalmandlecha/LP2_projects.git
```

### 6. Build and Deploy the Frontend

Build the frontend with the public backend URL:

```bash
cd LP2_projects/mern-event-registration/frontend
npm install
```

Create `frontend/.env`:

```env
VITE_API_URL=http://YOUR_PUBLIC_IP:5000/api/events
```

Build the frontend and move the built files to the Nginx web root:

```bash
npm run build
sudo rm -rf /var/www/html/*
sudo cp -r dist/* /var/www/html/
sudo systemctl reload nginx
```

Open the app in a browser:

```text
http://YOUR_PUBLIC_IP
```

### 7. Run the Backend

```bash
cd ../backend
npm install
# backend/.env is already included in this repo; edit it only if your port or database name changes.
npm start
```

The backend should be available at:

```text
http://YOUR_PUBLIC_IP:5000/api/events
```


## 📊 API Interface

- `GET /api/events` - Retrieve all event details.
- `POST /api/events` - Register a new event.
- `PUT /api/events/:id` - Edit event schedules/metadata.
- `DELETE /api/events/:id` - Cancel/Remove event record.

## 🛠️ Troubleshooting

- **Version Mismatch:** Ensure you are using **Node.js 18+**. The dependencies in this project are optimized for modern Node runtimes.
- **Database not found:** Ensure the `event-db` is correctly specified in your `.env`.
- **Frontend API URL:** Use `127.0.0.1` instead of `localhost` in your `.env` to avoid connection drops.
- **Node Modules:** If errors occur, delete `node_modules` and `package-lock.json` and run `npm install` again.

---

_Developed for Academic Practical Examination - Cloud Computing & LP2._
