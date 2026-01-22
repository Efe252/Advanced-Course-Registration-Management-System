/* --- NOTIFICATION ENGINE --- */
const Notify = {
    stack: document.getElementById('notify-stack'),
    show(msg, type = 'info', duration = 3000) {
        const el = document.createElement('div');
        el.className = `toast t-${type}`;
        el.innerHTML = `<div class="toast-content"><div class="toast-title">${type.toUpperCase()}</div><div class="toast-msg">${msg}</div></div>`;
        el.style.setProperty('animation-duration', '0.4s, ' + (duration/1000) + 's');
        this.stack.appendChild(el);
        setTimeout(() => { el.classList.add('out'); el.addEventListener('animationend', () => el.remove()); }, duration);
    }
};

/* --- LOGIC ENGINE --- */
const DB = {
    get: () => JSON.parse(localStorage.getItem('crms_v2')) || {},
    set: (d) => localStorage.setItem('crms_v2', JSON.stringify(d))
};

const App = {
    currentUser: null,

    init() {
        setTimeout(() => { document.getElementById('preloader').style.opacity = '0'; setTimeout(() => document.getElementById('preloader').remove(), 500); }, 800);
        if(localStorage.getItem('theme') === 'dark') document.body.setAttribute('data-theme', 'dark');
    },

    toggleTheme() {
        if(document.body.getAttribute('data-theme') === 'dark') {
            document.body.removeAttribute('data-theme'); localStorage.setItem('theme', 'light');
        } else {
            document.body.setAttribute('data-theme', 'dark'); localStorage.setItem('theme', 'dark');
        }
    },

    togglePass(id) {
        const el = document.getElementById(id);
        el.type = el.type === 'password' ? 'text' : 'password';
    },

    /* --- REGISTRATION LOGIC --- */
    register() {
        const name = document.getElementById('regName').value.trim();
        const pass = document.getElementById('regPass').value.trim();
        const code = document.getElementById('regCode').value.trim().toUpperCase();
        const unit = document.getElementById('regUnit').value;
        const lect = document.getElementById('regLecturer').value;

        if (!name || !pass || !code) {
            Notify.show('Name, Password, and Course Code are required.', 'error');
            return;
        }

        const db = DB.get();
        let user = db[name];

        if (user) {
            if (user.password !== pass) {
                Notify.show('Incorrect password for this user.', 'error');
                return;
            }
        } else {
            user = { password: pass, courses: [] };
            Notify.show('New profile created!', 'info');
        }

        if (user.courses.some(c => c.code === code)) {
            Notify.show('Course already registered.', 'warning');
            return;
        }

        user.courses.push({ code, unit, lect, ts: Date.now() });
        db[name] = user;
        DB.set(db);
        
        Notify.show(`Successfully registered ${code}`, 'success');
        this.loadDashboard(name);
    },

    /* --- LOGIN LOGIC --- */
    openLogin() { document.getElementById('modal-login').classList.add('active'); },
    closeLogin() { document.getElementById('modal-login').classList.remove('active'); },
    processLogin() {
        const name = document.getElementById('loginName').value.trim();
        const pass = document.getElementById('loginPass').value.trim();
        
        if(!name || !pass) { Notify.show('Enter credentials.', 'error'); return; }
        
        const db = DB.get();
        if(db[name] && db[name].password === pass) {
            this.closeLogin();
            Notify.show('Welcome back!', 'success');
            this.loadDashboard(name);
        } else {
            Notify.show('Invalid Username or Password.', 'error');
        }
    },

    /* --- DASHBOARD LOGIC --- */
    loadDashboard(name) {
        this.currentUser = name;
        document.getElementById('view-reg').classList.remove('active');
        document.getElementById('view-dash').classList.add('active');
        
        // Reset Forms
        ['regName','regPass','regCode','regUnit','regLecturer','loginName','loginPass'].forEach(id => document.getElementById(id).value = '');

        // Fill Data
        document.getElementById('d-name').textContent = name;
        document.getElementById('d-avatar').textContent = name.slice(0,2).toUpperCase();
        
        const user = DB.get()[name];
        const courses = user.courses || [];
        
        document.getElementById('d-count').textContent = courses.length;
        document.getElementById('d-units').textContent = courses.reduce((a,b) => a + (parseInt(b.unit)||0), 0);

        const list = document.getElementById('course-list');
        list.innerHTML = '';
        if(courses.length === 0) list.innerHTML = '<div style="padding:20px; text-align:center; color:var(--text-sub)">No courses found.</div>';

        courses.forEach(c => {
            list.innerHTML += `
                <div class="course-item">
                    <div>
                        <div style="font-weight:700; font-size:16px;">${c.code}</div>
                        <div style="font-size:12px; color:var(--text-sub); margin-top:4px;">${c.unit || 0} Units • ${c.lect || 'TBA'}</div>
                    </div>
                    <div style="color:var(--success)"><svg class="icon" viewBox="0 0 24 24"><polyline points="20 6 9 17 4 12"></polyline></svg></div>
                </div>`;
        });
    },

    logout() {
        const modal = document.getElementById('modal-confirm');
        document.getElementById('c-title').textContent = 'Secure Logout';
        document.getElementById('c-desc').textContent = 'End your current session?';
        modal.classList.add('active');
        
        document.getElementById('c-cancel').onclick = () => modal.classList.remove('active');
        document.getElementById('c-ok').onclick = () => {
            modal.classList.remove('active');
            this.currentUser = null;
            document.getElementById('view-dash').classList.remove('active');
            document.getElementById('view-reg').classList.add('active');
            Notify.show('Logged out successfully', 'info');
        };
    },

    returnToReg() {
        document.getElementById('regName').value = this.currentUser;
        document.getElementById('view-dash').classList.remove('active');
        document.getElementById('view-reg').classList.add('active');
        Notify.show('Add courses for ' + this.currentUser, 'info');
    }
};

App.init();
